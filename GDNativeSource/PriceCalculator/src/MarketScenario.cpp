#include "MarketScenario.h"
#include "Market.h"
#include "Person.h"
#include "Product.h"
#include "Prices.h"
#include "Reality.h"
#include "SatisfactionCalculator.h"
#include "Option.h"
#include "SupplCombo.h"
#include "ComplCombo.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace pca {

// Helper functions for JSON serialization of PersonData
void to_json(json& j, const CMarketScenario::PersonData& p) {
    j = json{
        {"name", p.sName},
        {"owned_products", p.mapOwnedProducts},
        {"option_satisfaction", p.mapOptionSatisfaction},
        {"suppl_satisfaction", p.mapSupplSatisfaction},
        {"compl_satisfaction", p.mapComplSatisfaction}
    };
}

void from_json(const json& j, CMarketScenario::PersonData& p) {
    j.at("name").get_to(p.sName);
    j.at("owned_products").get_to(p.mapOwnedProducts);
    j.at("option_satisfaction").get_to(p.mapOptionSatisfaction);
    j.at("suppl_satisfaction").get_to(p.mapSupplSatisfaction);
    j.at("compl_satisfaction").get_to(p.mapComplSatisfaction);
}

void to_json(json& j, const CMarketScenario::RealityData& r) {
    j = json{
        {"products", r.vProducts},
        {"option_to_product", r.mapOptionToProduct},
        {"compl_combos", r.mapComplCombos},
        {"suppl_combos", r.mapSupplCombos}
    };
}

void from_json(const json& j, CMarketScenario::RealityData& r) {
    j.at("products").get_to(r.vProducts);
    j.at("option_to_product").get_to(r.mapOptionToProduct);
    j.at("compl_combos").get_to(r.mapComplCombos);
    j.at("suppl_combos").get_to(r.mapSupplCombos);
}

CMarketScenario::CMarketScenario() {}
CMarketScenario::~CMarketScenario() {}

void CMarketScenario::Capture(CMarket* pMarket) {
    if (!pMarket) return;

    CaptureReality(pMarket->GetRealityRef());

    m_vPersonsData.clear();
    m_mapPrices.clear();
    m_mapMarketWarehouse.clear();

    // 1. Capturar Precios
    CPrices* pPrices = pMarket->GetPricesRef();
    auto vProducts = pMarket->GetProducts();
    for (auto* pProd : vProducts) {
        m_mapPrices[pProd->GetName()] = pPrices->GetPriceOfProduct(pProd);
    }

    // 2. Capturar Almacén del Mercado
    auto mapExcess = pMarket->GetExcessProducts();
    for (auto& pair : mapExcess) {
        m_mapMarketWarehouse[pair.first->GetName()] = pair.second;
    }

    // 3. Capturar Datos de Personas
    auto vPersons = pMarket->GetPersons();
    CReality* pReality = pMarket->GetRealityRef();
    auto vOptions = pMarket->GetOptions();
    auto vSuppl = pReality->GetSupplCombos();
    auto vCompl = pReality->GetComplCombos();

    for (auto* pPerson : vPersons) {
        PersonData data;
        data.sName = pPerson->GetName();

        // Inventario
        for (auto* pProd : vProducts) {
            data.mapOwnedProducts[pProd->GetName()] = pPerson->GetOwnedProdAmount(pProd);
        }

        // Curvas de Satisfacción
        CSatisfactionCalculator* pSatCalc = pPerson->GetSatisfactionCalculatorRef();
        if (pSatCalc) {
            for (auto* pOpt : vOptions) {
                data.mapOptionSatisfaction[pOpt->GetName()] = {
                    pSatCalc->GetPreferenceAt0(pOpt),
                    pSatCalc->GetMaximumSatisf(pOpt)
                };
            }
            for (auto* pS : vSuppl) {
                data.mapSupplSatisfaction[pS->GetName()] = {
                    pSatCalc->GetPreferenceAt0(pS),
                    pSatCalc->GetMaximumSatisf(pS)
                };
            }
            for (auto* pC : vCompl) {
                data.mapComplSatisfaction[pC->GetName()] = {
                    pSatCalc->GetPreferenceAt0(pC),
                    pSatCalc->GetMaximumSatisf(pC)
                };
            }
        }
        m_vPersonsData.push_back(data);
    }
}

void CMarketScenario::Apply(CMarket* pMarket) {
    if (!pMarket) return;

    ApplyReality(pMarket->GetRealityRef());

    CReality* pReality = pMarket->GetRealityRef();
    CPrices* pPrices = pMarket->GetPricesRef();

    // 1. Aplicar Precios
    for (auto& pair : m_mapPrices) {
        CProduct* pProd = pReality->GetProduct(pair.first);
        if (pProd) {
            pPrices->SetPriceOfProduct(pProd, pair.second);
        }
    }

    // 2. Aplicar Almacén
    std::map<CProduct*, double> mapWarehouse;
    for (auto& pair : m_mapMarketWarehouse) {
        CProduct* pProd = pReality->GetProduct(pair.first);
        if (pProd) mapWarehouse[pProd] = pair.second;
    }
    pMarket->SetExcessProducts(mapWarehouse);

    // 3. Aplicar Personas
    for (const auto& data : m_vPersonsData) {
        CPerson* pPerson = pMarket->GetPersonRef(data.sName);
        
        // Si no existe en el mercado destino, lo creamos
        if (!pPerson) {
            pPerson = pMarket->CreatePerson(data.sName);
        }

        if (pPerson) {
            // Restaurar Inventario
            std::map<CProduct*, double> mapInv;
            for (auto& pairP : data.mapOwnedProducts) {
                CProduct* pProd = pReality->GetProduct(pairP.first);
                if (pProd) mapInv[pProd] = pairP.second;
            }
            pPerson->SetOwnedProducts(mapInv);

            // Restaurar Curvas
            CSatisfactionCalculator* pSatCalc = pPerson->GetSatisfactionCalculatorRef();
            if (pSatCalc) {
                for (auto& pairO : data.mapOptionSatisfaction) {
                    COption* pOpt = pReality->GetOption(pairO.first);
                    if (pOpt) {
                        pSatCalc->SetPreferenceAt0(pOpt, pairO.second.first);
                        pSatCalc->SetMaximumSatisf(pOpt, pairO.second.second);
                    }
                }
                for (auto& pairS : data.mapSupplSatisfaction) {
                    CSupplCombo* pS = pReality->GetSupplCombo(pairS.first);
                    if (pS) {
                        pSatCalc->SetPreferenceAt0(pS, pairS.second.first);
                        pSatCalc->SetMaximumSatisf(pS, pairS.second.second);
                    }
                }
                for (auto& pairC : data.mapComplSatisfaction) {
                    CComplCombo* pC = pReality->GetComplCombo(pairC.first);
                    if (pC) {
                        pSatCalc->SetPreferenceAt0(pC, pairC.second.first);
                        pSatCalc->SetMaximumSatisf(pC, pairC.second.second);
                    }
                }
            }
        }
    }
}

bool CMarketScenario::SaveToFile(const std::string& sFilePath) {
    try {
        json j;
        j["reality"] = m_realityData;
        j["prices"] = m_mapPrices;
        j["market_warehouse"] = m_mapMarketWarehouse;
        j["persons"] = m_vPersonsData;

        std::ofstream file(sFilePath);
        if (file.is_open()) {
            file << j.dump(4);
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error saving scenario to JSON: " << e.what() << std::endl;
    }
    return false;
}

bool CMarketScenario::LoadFromFile(const std::string& sFilePath) {
    try {
        std::ifstream file(sFilePath);
        if (file.is_open()) {
            json j;
            file >> j;
            m_realityData = j.at("reality").get<RealityData>();
            m_mapPrices = j.at("prices").get<std::map<std::string, double>>();
            m_mapMarketWarehouse = j.at("market_warehouse").get<std::map<std::string, double>>();
            m_vPersonsData = j.at("persons").get<std::vector<PersonData>>();
            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading scenario from JSON: " << e.what() << std::endl;
    }
    return false;
}

void CMarketScenario::CaptureReality(CReality* pReality) {
    if (!pReality) return;

    m_realityData.vProducts.clear();
    m_realityData.mapOptionToProduct.clear();
    m_realityData.mapComplCombos.clear();
    m_realityData.mapSupplCombos.clear();

    // 1. Productos
    for (auto* pProd : pReality->GetProducts()) {
        m_realityData.vProducts.push_back(pProd->GetName());
    }

    // 2. Opciones
    for (auto* pOpt : pReality->GetOptions()) {
        if (pOpt->GetProduct()) {
            m_realityData.mapOptionToProduct[pOpt->GetName()] = pOpt->GetProduct()->GetName();
        }
    }

    // 3. ComplCombos
    for (auto* pCC : pReality->GetComplCombos()) {
        std::vector<std::string> vOpts;
        for (auto* pO : pCC->GetOptions()) {
            vOpts.push_back(pO->GetName());
        }
        m_realityData.mapComplCombos[pCC->GetName()] = vOpts;
    }

    // 4. SupplCombos
    for (auto* pSC : pReality->GetSupplCombos()) {
        std::map<std::string, double> mapWeights;
        for (auto& pair : pSC->GetOptionsAndWeights()) {
            mapWeights[pair.first->GetName()] = pair.second;
        }
        m_realityData.mapSupplCombos[pSC->GetName()] = mapWeights;
    }
}

void CMarketScenario::ApplyReality(CReality* pReality) {
    if (!pReality || m_realityData.vProducts.empty()) return;

    // Limpiamos la realidad destino para que sea idéntica a la guardada
    pReality->Clear();
    pReality->InitEmpty();

    // 1. Reconstruir Productos
    for (const auto& sProd : m_realityData.vProducts) {
        pReality->CreateProduct(sProd);
    }

    // 2. Reconstruir Opciones
    for (const auto& pair : m_realityData.mapOptionToProduct) {
        pReality->CreateOption(pair.second, pair.first);
    }

    // 3. Reconstruir ComplCombos
    for (const auto& pair : m_realityData.mapComplCombos) {
        pReality->CreateComplCombo(pair.first);
        for (const auto& sOpt : pair.second) {
            pReality->AddOptionToComplCombo(pair.first, sOpt);
        }
    }

    // 4. Reconstruir SupplCombos
    for (const auto& pair : m_realityData.mapSupplCombos) {
        pReality->CreateSupplCombo(pair.first);
        for (const auto& pairW : pair.second) {
            pReality->AddOptionToSupplCombo(pair.first, pairW.first, pairW.second);
        }
    }
}

} // namespace pca
