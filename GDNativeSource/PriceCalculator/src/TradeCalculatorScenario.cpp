#include "TradeCalculatorScenario.h"
#include "Person.h"
#include "Prices.h"
#include "Product.h"
#include "Option.h"
#include "Market.h"
#include "Reality.h"
#include "TradeCalculator.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"
#include "Utils.h"

#include <assert.h>

#include <iostream>



pca::CTradeCalculatorScenario::CTradeCalculatorScenario()
{

    std::cout << "Price Calculator constructor." << std::endl;
}

pca::CTradeCalculatorScenario::~CTradeCalculatorScenario()
{
    //dtor
    std::cout << "Price Calculator destructor." << std::endl;
}

int pca::CTradeCalculatorScenario::GetTestPrice()
{
    return 8;
}

void pca::CTradeCalculatorScenario::CreateEmptyMarket()
{
    if (m_upReality)
    {
        std::unique_ptr<CMarket> upMarket(new CMarket(m_upReality.get()));
        
        m_upReality.get()->AddMarket(upMarket);
    }
    else
    {
        assert("" == "Falta una realidad donde añadir este nuevo Market");
    }
}

void pca::CTradeCalculatorScenario::CreateEmptyReality()
{
    m_upReality.reset();
    std::unique_ptr<CReality> upReality(new CReality(false));
    m_upReality = std::move(upReality);
}

void pca::CTradeCalculatorScenario::CreateTradeCalculator()
{
    if (nullptr != m_upReality && nullptr != m_upReality->GetLastMarketRef())
    {
        m_upTradeCalculator.reset();
        std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator(new CSatisfactionCalculator(m_upReality->GetLastMarketRef()));

        std::unique_ptr<CTradeCalculator> upTradeCalculator(new CTradeCalculator(std::move(upSatisfactionCalculator), m_upReality->GetLastMarketRef()->GetPricesRef(), m_upReality->GetLastMarketRef()));
        m_upTradeCalculator = std::move(upTradeCalculator);
    }
}

void pca::CTradeCalculatorScenario::CreateProduct(std::string sProductName)
{
    m_upReality->CreateProduct(sProductName);
}

void pca::CTradeCalculatorScenario::SetCurrency(std::string sProductName)
{
    if (nullptr == m_upReality || nullptr == m_upReality->GetLastMarketRef())
    {
        if (nullptr == m_upReality)
            std::cout << "pca::CPriceCalculator::SetCurrency needs a m_upReality before being called"<<std::endl;
        else if (nullptr == m_upReality->GetLastMarketRef())
            std::cout << "pca::CPriceCalculator::SetCurrency needs a market inside m_upReality before being called" << std::endl;

        return;
    }

    CPrices* pPricesRef = m_upReality->GetLastMarketRef()->GetPricesRef();

    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pPricesRef && pProductRef)
    {
        if (false == pPricesRef->IsCurrency(pProductRef))
        {
            pPricesRef->SetCurrency(pProductRef);
        }
    }
}

void pca::CTradeCalculatorScenario::AddToProduct_CreateConsumptionOption(std::string sProduct, std::string sOption)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProduct);
    if (pProductRef)
    {
        m_upReality->CreateOption(sProduct, sOption);
    }
}

//void pca::CTradeCalculatorScenario::AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
//{
//    if (nullptr == m_upReality->GetLastMarketRef())
//        return;
//
//    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);
//    COption* pOptionRef = m_upReality->GetOption(sOption);
//
//    if (pPersonRef && pOptionRef)
//    {
//        pca::CSatisfactionCalculator* pSatCalculator = pPersonRef->GetTradeCalculatorRef()->GetSatisfactionCalculatorRef();
//        pSatCalculator->SetPreferenceAt0(pOptionRef, dValueAt0);
//        pSatCalculator->SetMaximumSatisf(pOptionRef, dMaxValue);        
//    }
//}

void pca::CTradeCalculatorScenario::SetSatisfactionCurveForOption(std::string sOption, double dValueAt0, double dMaxValue)
{
    if (nullptr == m_upReality->GetLastMarketRef())
        return;
    
    COption* pOptionRef = m_upReality->GetOption(sOption);

    if (pOptionRef && m_upTradeCalculator)
    {
        
        pca::CSatisfactionCalculator* pSatCalculator = m_upTradeCalculator->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pOptionRef, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pOptionRef, dMaxValue);
    }
}

std::map<std::string, double> pca::CTradeCalculatorScenario::AdjustBestCombidict(double dBudgetArg, std::map<COption*, double> mapCurrentCombidictArg, double dBudgetStepArg, int nMaxStepArg)
{
    if (nullptr == m_upReality || nullptr == m_upReality->GetLastMarketRef() || nullptr == m_upTradeCalculator)
        return std::map<std::string, double>();

    std::map<std::string, double> mapOptionName_dAmount; 
    std::map <COption*, double > mapOption_dAmount= m_upTradeCalculator->AdjustBestCombidict(dBudgetArg, mapCurrentCombidictArg, dBudgetStepArg, nMaxStepArg);


    for (auto& pairOptionName_dAmount : mapOption_dAmount)
    {
        mapOptionName_dAmount[pairOptionName_dAmount.first->GetName()] = pairOptionName_dAmount.second;
    }

    return mapOptionName_dAmount;
}

bool pca::CTradeCalculatorScenario::IsProduct(std::string sProductName)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pProductRef)
    {
        return true;
    }

    return false;
}

bool pca::CTradeCalculatorScenario::IsPerson(std::string sPersonName)
{
    if (m_upReality && nullptr == m_upReality->GetLastMarketRef())
        return false;

    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPersonName);

    if (pPersonRef)
    {
        return true;
    }

    return false;
}

bool pca::CTradeCalculatorScenario::IsOption(std::string sOptionName)
{
    COption* pOptionRef = m_upReality->GetOption(sOptionName);

    if (pOptionRef)
    {
        return true;
    }

    return false;
}

std::string pca::CTradeCalculatorScenario::GetCurrency()
{
    if (m_upReality->GetLastMarketRef() && m_upReality->GetLastMarketRef()->GetPricesRef() && m_upReality->GetLastMarketRef()->GetPricesRef()->GetCurrency())
    {
        return m_upReality->GetLastMarketRef()->GetPricesRef()->GetCurrency()->GetName();
    }
    return "";
}

double pca::CTradeCalculatorScenario::GetPrice(std::string sProductName)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (m_upReality->GetLastMarketRef() && m_upReality->GetLastMarketRef()->GetPricesRef() && pProductRef)
    {
        return m_upReality->GetLastMarketRef()->GetPricesRef()->GetPriceOfProduct(pProductRef);
    }

    return 0.0;
}

double pca::CTradeCalculatorScenario::GetProductAmount(std::string sProductName, std::string sPerson)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef && pProductRef)
    {
        return pPersonRef->GetOwnedProdAmount(pProductRef);
    }

    return 0.0;

}

double pca::CTradeCalculatorScenario::GetOptionAmount(std::string sOptionName, std::string sPerson)
{
    COption* pOptionRef = m_upReality->GetOption(sOptionName);
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef && pOptionRef)
    {
        return pPersonRef->GetCurrentOptAmount(pOptionRef);
    }

    return 0.0;

}

double pca::CTradeCalculatorScenario::GetTradedAmount(std::string sProductName, std::string sPerson)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef && pProductRef)
    {
        return pPersonRef->GetTradedAmount(pProductRef);
    }

    return 0.0;

}


void pca::CTradeCalculatorScenario::PrintPricesEvolution()
{
    CUtils::PrintPricesEvolution(m_upReality->GetLastMarketRef());
}

double pca::CTradeCalculatorScenario::GetDesiredProdAmount(std::string sPerson, std::string sProductName)
{
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pPersonRef)
    {
        return pPersonRef->GetDesiredProdAmount(pProductRef);
    }

    return 0.0;

}

void pca::CTradeCalculatorScenario::PrintPersonOptionAdjustmentToFile(std::string sPerson)
{
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef)
    {
        pca::CUtils::PrintPersonOptionAdjustmentToFile(pPersonRef);        
    }
}

void pca::CTradeCalculatorScenario::PrintPersonsOptionAdjustmentToFile()
{
    if (m_upReality->GetLastMarketRef())
        pca::CUtils::PrintPersonsOptionAdjustmentToFile(m_upReality->GetLastMarketRef());
}


