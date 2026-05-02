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

namespace pca {

CMarketScenario::CMarketScenario() {}
CMarketScenario::~CMarketScenario() {}

void CMarketScenario::Capture(CMarket* pMarket) {
    if (!pMarket) return;

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

} // namespace pca
