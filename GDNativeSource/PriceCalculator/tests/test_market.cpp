#include "catch.hpp"
#include "Market.h"
#include "Reality.h"
#include "Person.h"
#include "Prices.h"
#include "MarketScenario.h"

using namespace pca;

TEST_CASE("Market scenarios can be captured and applied to new markets", "[market][scenario]") {
    CReality oReality;
    CMarket oMarket(&oReality);
    
    // GIVEN: A market with a person and specific prices
    CPerson* pP1 = oMarket.CreatePerson("Person A");
    CProduct* pChoc = oReality.GetProduct("chocolate");
    pP1->AddProductAmount(pChoc, 10.0);
    oMarket.GetPricesRef()->SetPriceOfProduct(pChoc, 12.5);
    
    // WHEN: We capture the scenario and apply it to a fresh market
    CMarketScenario oScenario;
    oScenario.Capture(&oMarket);
    
    CMarket oNewMarket(&oReality);
    oScenario.Apply(&oNewMarket);
    
    // THEN: The new market must have the same state
    CPerson* pP1_New = oNewMarket.GetPersonRef("Person A");
    REQUIRE(pP1_New != nullptr);
    CHECK(oNewMarket.GetPricesRef()->GetPriceOfProduct(pChoc) == 12.5);
    CHECK(pP1_New->GetOwnedProdAmount(pChoc) == 10.0);
}

TEST_CASE("Market warehouse inventory is correctly managed", "[market][warehouse]") {
    CReality oReality;
    CMarket oMarket(&oReality);
    CProduct* pChoc = oReality.GetProduct("chocolate");

    SECTION("Initial warehouse should be empty") {
        auto mapExcess = oMarket.GetExcessProducts();
        CHECK(mapExcess[pChoc] == 0.0);
    }

    SECTION("Applying a scenario with warehouse data") {
        CMarketScenario oScenario;
        oScenario.m_mapMarketWarehouse["chocolate"] = 50.0;
        oScenario.Apply(&oMarket);
        
        CHECK(oMarket.GetExcessProducts()[pChoc] == 50.0);
    }
}
