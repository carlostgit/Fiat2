#include "catch.hpp"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "Reality.h"
#include "Market.h"

using namespace pca;

TEST_CASE("Satisfaction Curve calculations", "[satisfaction]") {
    CSatisfactionCurve oSatCurve;

    SECTION("Satisfaction at zero quantity should be zero") {
        CHECK(oSatCurve.CalculateSatifaction(0) == 0.0);
    }

    SECTION("Satisfaction increases with quantity but follows diminishing returns") {
        double s1 = oSatCurve.CalculateSatifaction(1);
        double s2 = oSatCurve.CalculateSatifaction(2);
        double s10 = oSatCurve.CalculateSatifaction(10);
        
        CHECK(s1 > 0.0);
        CHECK(s2 > s1);
        CHECK((s2 - s1) > (s10 - oSatCurve.CalculateSatifaction(9))); // Rendimientos decrecientes
    }
}

TEST_CASE("Satisfaction Calculator integrates combos", "[satisfaction][calculator]") {
    CReality oReality;
    CMarket oMarket(&oReality);
    CSatisfactionCalculator oSatCalculator(&oMarket);
    
    std::map<COption*, double> map_nOption_dAmount;
    for (auto* nOption : oReality.GetOptions()) {
        map_nOption_dAmount[nOption] = 1.0;
    }

    double dTotal = oSatCalculator.CalculateSatisfOfCombidict(map_nOption_dAmount);
    
    CHECK(dTotal > 0.0);
}
