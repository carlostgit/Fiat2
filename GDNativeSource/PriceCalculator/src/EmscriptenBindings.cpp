#include <emscripten/bind.h>
#include "Market.h"
#include "Reality.h"
#include "MarketScenario.h"
#include "Product.h"
#include "Prices.h"
#include <string>
#include <nlohmann/json.hpp>

using namespace emscripten;
using namespace pca;
using json = nlohmann::json;

class CEmscriptenRunner {
public:
    CEmscriptenRunner() : m_oMarket(&m_oReality) {}

    // Cargar un escenario completo desde un string JSON
    bool loadScenario(std::string sJson) {
        try {
            json j = json::parse(sJson);
            CMarketScenario scenario;
            
            // Llenar los datos del escenario desde el JSON
            scenario.m_realityData = j.at("reality").get<CMarketScenario::RealityData>();
            scenario.m_mapPrices = j.at("prices").get<std::map<std::string, double>>();
            scenario.m_mapMarketWarehouse = j.at("market_warehouse").get<std::map<std::string, double>>();
            scenario.m_vPersonsData = j.at("persons").get<std::vector<CMarketScenario::PersonData>>();
            
            scenario.Apply(&m_oMarket);
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    // Ejecutar un paso de la simulación
    void step() {
        m_oMarket.CalculateNewPrices();
        m_oMarket.ExecuteTrades();
    }

    // Obtener el estado actual del escenario como JSON
    std::string getScenarioJson() {
        CMarketScenario scenario;
        scenario.Capture(&m_oMarket);
        
        json j;
        j["reality"] = scenario.m_realityData;
        j["prices"] = scenario.m_mapPrices;
        j["market_warehouse"] = scenario.m_mapMarketWarehouse;
        j["persons"] = scenario.m_vPersonsData;
        
        return j.dump();
    }

    // Obtener solo los precios actuales
    std::string getPricesJson() {
        json j = std::map<std::string, double>();
        CPrices* pPrices = m_oMarket.GetPricesRef();
        for (auto* pProd : m_oMarket.GetProducts()) {
            j[pProd->GetName()] = pPrices->GetPriceOfProduct(pProd);
        }
        return j.dump();
    }

private:
    CReality m_oReality;
    CMarket m_oMarket;
};

// Vinculación con Emscripten (Embind)
EMSCRIPTEN_BINDINGS(market_runner) {
    class_<CEmscriptenRunner>("MarketRunner")
        .constructor<>()
        .function("loadScenario", &CEmscriptenRunner::loadScenario)
        .function("step", &CEmscriptenRunner::step)
        .function("getScenarioJson", &CEmscriptenRunner::getScenarioJson)
        .function("getPricesJson", &CEmscriptenRunner::getPricesJson);
}
