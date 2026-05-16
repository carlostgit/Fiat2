#include "catch.hpp"
#include "../src/Market.h"
#include "../src/Reality.h"
#include "../src/Person.h"
#include "../src/Prices.h"
#include "../src/MarketScenario.h"

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
    CProduct* pChoc_New = oReality.GetProduct("chocolate");
    CPerson* pP1_New = oNewMarket.GetPersonRef("Person A");
    REQUIRE(pP1_New != nullptr);
    REQUIRE(pChoc_New != nullptr);
    CHECK(oNewMarket.GetPricesRef()->GetPriceOfProduct(pChoc_New) == 12.5);
    CHECK(pP1_New->GetOwnedProdAmount(pChoc_New) == 10.0);
}

TEST_CASE("Market scenarios can be saved to and loaded from JSON",
          "[market][scenario][json]") {
    CReality oReality;
    CMarket oMarket(&oReality);
    
    // GIVEN: A scenario with data
  CPerson *pP1 = oMarket.CreatePerson("Person JSON");
  CProduct *pChoc = oReality.GetProduct("chocolate");
    pP1->AddProductAmount(pChoc, 50.0);
    oMarket.GetPricesRef()->SetPriceOfProduct(pChoc, 99.9);
    
    CMarketScenario oScenarioSave;
    oScenarioSave.Capture(&oMarket);
    
    // WHEN: We save to file and load into a new scenario object
    std::string sTestFile = "test_scenario.json";
    REQUIRE(oScenarioSave.SaveToFile(sTestFile));
    
    CMarketScenario oScenarioLoad;
    REQUIRE(oScenarioLoad.LoadFromFile(sTestFile));
    
    // THEN: Applying the loaded scenario should yield the same results
    CMarket oNewMarket(&oReality);
    oScenarioLoad.Apply(&oNewMarket);
    
  // IMPORTANTE: Después de ApplyReality, los punteros antiguos de oReality son
  // INVÁLIDOS
  CProduct *pChoc_New = oReality.GetProduct("chocolate");
  CPerson *pP1_New = oNewMarket.GetPersonRef("Person JSON");
    
    REQUIRE(pP1_New != nullptr);
    REQUIRE(pChoc_New != nullptr);
    CHECK(oNewMarket.GetPricesRef()->GetPriceOfProduct(pChoc_New) == 99.9);
    CHECK(pP1_New->GetOwnedProdAmount(pChoc_New) == 50.0);
    
    // Clean up
    std::remove(sTestFile.c_str());
}

TEST_CASE("Market scenario captures and applies Reality structure",
          "[market][scenario][reality]") {
    // 1. Crear una realidad personalizada
    CReality oReality(false); // Vacía
    oReality.InitEmpty();
    oReality.CreateProduct("gold");
    oReality.CreateOption("gold", "jewelry");
    oReality.CreateComplCombo("luxury");
    oReality.AddOptionToComplCombo("luxury", "jewelry");
    
    CMarket oMarket(&oReality);
  oMarket.GetPricesRef()->SetPriceOfProduct(oReality.GetProduct("gold"),
                                            1500.0);
    
    CMarketScenario oScenario;
    oScenario.Capture(&oMarket);
    
    // 2. Guardar y cargar
    std::string sFile = "test_reality.json";
    REQUIRE(oScenario.SaveToFile(sFile));
    
    CMarketScenario oLoaded;
    REQUIRE(oLoaded.LoadFromFile(sFile));
    
    // 3. Aplicar a una realidad nueva y vacía
    CReality oNewReality(false);
    CMarket oNewMarket(&oNewReality);
    oLoaded.Apply(&oNewMarket);
    
    // 4. Verificar estructura
    CHECK(oNewReality.GetProduct("gold") != nullptr);
    CHECK(oNewReality.GetOption("jewelry") != nullptr);
    CHECK(oNewReality.GetComplCombo("luxury") != nullptr);
  CHECK(oNewMarket.GetPricesRef()->GetPriceOfProduct(
            oNewReality.GetProduct("gold")) == 1500.0);
    
    std::remove(sFile.c_str());
}

TEST_CASE("Market warehouse inventory is correctly managed",
          "[market][warehouse]") {
    CReality oReality;
    CMarket oMarket(&oReality);
  CProduct *pChoc = oReality.GetProduct("chocolate");

    SECTION("Initial warehouse should be empty") {
        auto mapExcess = oMarket.GetExcessProducts();
        CHECK(mapExcess[pChoc] == 0.0);
    }

    SECTION("Applying a scenario with warehouse data") {
        CMarketScenario oScenario;
        oScenario.m_mapMarketWarehouse["chocolate"] = 50.0;
        oScenario.Apply(&oMarket);
        
    CProduct *pChoc_New = oReality.GetProduct("chocolate");
        CHECK(oMarket.GetExcessProducts()[pChoc_New] == 50.0);
    }
}
