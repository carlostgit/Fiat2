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

void pca::CTradeCalculatorScenario::SetPrice(std::string sProductName, double dPrice)
{
    if (nullptr == m_upReality || nullptr == m_upReality->GetLastMarketRef())
    {
        if (nullptr == m_upReality)
            std::cout << "pca::CPriceCalculator::SetCurrency needs a m_upReality before being called" << std::endl;
        else if (nullptr == m_upReality->GetLastMarketRef())
            std::cout << "pca::CPriceCalculator::SetCurrency needs a market inside m_upReality before being called" << std::endl;

        return;
    }

    CPrices* pPricesRef = m_upReality->GetLastMarketRef()->GetPricesRef();

    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pPricesRef && pProductRef)
    {
        pPricesRef->SetPriceOfProduct(pProductRef,dPrice);
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

void pca::CTradeCalculatorScenario::CreateComplCombo(std::string sComplCombo)
{
    if (nullptr == m_upReality)
    {
        std::cout << "pca::CPriceCalculator::CreateComplCombo needs a m_upReality before being called" << std::endl;
        return;
    }

    m_upReality->CreateComplCombo(sComplCombo);

    //CComplCombo* pComplComboRef = m_upReality->GetComplCombo(sComplCombo);

    //if (nullptr == pComplComboRef)
    //{
    //    std::cout << "error using pca::CPriceCalculator::CreateComplCombo. ComplCombo " << sComplCombo << " not found" << std::endl;
    //    return;
    //}

    //if (pComplComboRef)
    //{
    //    m_upReality->CreateComplCombo(sComplCombo);
    //}
}

void pca::CTradeCalculatorScenario::AddOptionToComplCombo(std::string sComplCombo, std::string sOption)
{
    if (nullptr == m_upReality)
    {
        std::cout << "pca::CPriceCalculator::AddOptionToComplCombo needs a m_upReality before being called" << std::endl;
        return;
    }

    CComplCombo* pComplComboRef = m_upReality->GetComplCombo(sComplCombo);

    if (nullptr == pComplComboRef)
    {
        std::cout << "error using pca::CPriceCalculator::AddOptionToComplCombo. ComplCombo " << sComplCombo << " not found" << std::endl;
        return;
    }

    COption* pOptionRef = m_upReality->GetOption(sOption);

    if (nullptr == pOptionRef)
    {
        std::cout << "error using pca::CPriceCalculator::AddOptionToComplCombo. Option " << sOption << " not found" << std::endl;
        return;
    }

    m_upReality->AddOptionToComplCombo(sComplCombo, sOption);
}

void pca::CTradeCalculatorScenario::CreateSupplCombo(std::string sSupplCombo)
{
    if (nullptr == m_upReality)
    {
        std::cout << "pca::CPriceCalculator::CreateSupplCombo needs a m_upReality before being called" << std::endl;
        return;
    }

    m_upReality->CreateSupplCombo(sSupplCombo);

    //CSupplCombo* pSupplComboRef = m_upReality->GetSupplCombo(sSupplCombo);

    //if (nullptr == pSupplComboRef)
    //{
    //    std::cout << "error using pca::CPriceCalculator::CreateSupplCombo. ComplCombo " << sSupplCombo << " not found" << std::endl;
    //    return;
    //}

    //if (pSupplComboRef)
    //{
    //    m_upReality->CreateSupplCombo(sSupplCombo);
    //}
}

void pca::CTradeCalculatorScenario::AddOptionToSupplCombo(std::string sSupplCombo, std::string sOption, double dWeight)
{
    if (nullptr == m_upReality)
    {
        std::cout << "pca::CPriceCalculator::AddOptionToSupplCombo needs a m_upReality before being called" << std::endl;
        return;
    }

    CSupplCombo* pComplComboRef = m_upReality->GetSupplCombo(sSupplCombo);

    if (nullptr == pComplComboRef)
    {
        std::cout << "error using pca::CPriceCalculator::AddOptionToSupplCombo. ComplCombo " << sSupplCombo << " not found" << std::endl;
        return;
    }

    COption* pOptionRef = m_upReality->GetOption(sOption);

    if (nullptr == pOptionRef)
    {
        std::cout << "error using pca::CPriceCalculator::AddOptionToComplCombo. Option " << sOption << " not found" << std::endl;
        return;
    }

    m_upReality->AddOptionToComplCombo(sSupplCombo, sOption);
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

void pca::CTradeCalculatorScenario::SetSatisfactionCurveForComplementaryCombo(std::string sComplementaryCombo, double dValueAt0, double dMaxValue)
{
    if (nullptr == m_upReality->GetLastMarketRef())
        return;

    //COption* pOptionRef = m_upReality->GetOption(sOption);

    pca::CComplCombo* pComplementaryCombo = m_upReality->GetComplCombo(sComplementaryCombo);

    if (pComplementaryCombo && m_upTradeCalculator)
    {

        pca::CSatisfactionCalculator* pSatCalculator = m_upTradeCalculator->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pComplementaryCombo, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pComplementaryCombo, dMaxValue);
    }
}

void pca::CTradeCalculatorScenario::SetSatisfactionCurveForSupplementaryCombo(std::string sSupplementaryCombo, double dValueAt0, double dMaxValue)
{
    if (nullptr == m_upReality->GetLastMarketRef())
        return;

    //COption* pOptionRef = m_upReality->GetOption(sOption);

    pca::CSupplCombo* pSupplementaryCombo = m_upReality->GetSupplCombo(sSupplementaryCombo);

    if (pSupplementaryCombo && m_upTradeCalculator)
    {

        pca::CSatisfactionCalculator* pSatCalculator = m_upTradeCalculator->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pSupplementaryCombo, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pSupplementaryCombo, dMaxValue);
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


