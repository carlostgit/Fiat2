#include "PriceCalculator.h"
#include "Person.h"
#include "Prices.h"
#include "Product.h"
#include "Market.h"
#include "Reality.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"
#include "Utils.h"

#include <assert.h>

#include <iostream>



pca::CPriceCalculator::CPriceCalculator()
{

    std::cout << "Price Calculator constructor." << std::endl;
}

pca::CPriceCalculator::~CPriceCalculator()
{
    //dtor
    std::cout << "Price Calculator destructor." << std::endl;
}

int pca::CPriceCalculator::GetTestPrice()
{
    return 8;
}

void pca::CPriceCalculator::CreateEmptyMarket()
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

void pca::CPriceCalculator::CreateEmptyReality()
{
    m_upReality.reset();
    std::unique_ptr<CReality> upReality(new CReality(false));
    m_upReality = std::move(upReality);
}

void pca::CPriceCalculator::CreateProduct(std::string sProductName)
{
    m_upReality->CreateProduct(sProductName);
}

void pca::CPriceCalculator::SetCurrency(std::string sProductName)
{
    if (nullptr == m_upReality || nullptr == m_upReality->GetLastMarketRef())
        return;

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

void pca::CPriceCalculator::AddToProduct_CreateConsumptionOption(std::string sProduct, std::string sOption)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProduct);
    if (pProductRef)
    {
        m_upReality->CreateOption(sProduct, sOption);
    }
}

void pca::CPriceCalculator::AddToMarket_CreatePerson(std::string sPerson)
{
    if (m_upReality->GetLastMarketRef())
        m_upReality->GetLastMarketRef()->CreatePerson(sPerson);
}

void pca::CPriceCalculator::AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount)
{
    if (nullptr == m_upReality->GetLastMarketRef())
        return;

    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);
    CProduct* pProductRef = m_upReality->GetProduct(sProduct);

    if (pPersonRef && pProductRef)
    {
        pPersonRef->AddProductAmount(pProductRef, dAmount);
    }
}

void pca::CPriceCalculator::AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
{
    if (nullptr == m_upReality->GetLastMarketRef())
        return;

    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);
    COption* pOptionRef = m_upReality->GetOption(sOption);

    if (pPersonRef && pOptionRef)
    {
        pca::CSatisfactionCalculator* pSatCalculator = pPersonRef->GetTradeCalculatorRef()->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pOptionRef, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pOptionRef, dMaxValue);        
    }
}

void pca::CPriceCalculator::AdjustPrices()
{
    if (m_upReality->GetLastMarketRef())
        m_upReality->GetLastMarketRef()->CalculateNewPrices();

}
bool pca::CPriceCalculator::IsProduct(std::string sProductName)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pProductRef)
    {
        return true;
    }

    return false;
}

bool pca::CPriceCalculator::IsPerson(std::string sPersonName)
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

bool pca::CPriceCalculator::IsOption(std::string sOptionName)
{
    COption* pOptionRef = m_upReality->GetOption(sOptionName);

    if (pOptionRef)
    {
        return true;
    }

    return false;
}

std::string pca::CPriceCalculator::GetCurrency()
{
    if (m_upReality->GetLastMarketRef() && m_upReality->GetLastMarketRef()->GetPricesRef() && m_upReality->GetLastMarketRef()->GetPricesRef()->GetCurrency())
    {
        return m_upReality->GetLastMarketRef()->GetPricesRef()->GetCurrency()->GetName();
    }
    return "";
}

double pca::CPriceCalculator::GetPrice(std::string sProductName)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (m_upReality->GetLastMarketRef() && m_upReality->GetLastMarketRef()->GetPricesRef() && pProductRef)
    {
        return m_upReality->GetLastMarketRef()->GetPricesRef()->GetPriceOfProduct(pProductRef);
    }

    return 0.0;
}

double pca::CPriceCalculator::GetProductAmount(std::string sProductName, std::string sPerson)
{
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef && pProductRef)
    {
        return pPersonRef->GetOwnedProdAmount(pProductRef);
    }

    return 0.0;

}

double pca::CPriceCalculator::GetOptionAmount(std::string sOptionName, std::string sPerson)
{
    COption* pOptionRef = m_upReality->GetOption(sOptionName);
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef && pOptionRef)
    {
        return pPersonRef->GetCurrentOptAmount(pOptionRef);
    }

    return 0.0;

}

void pca::CPriceCalculator::PrintPricesEvolution()
{
    CUtils::PrintPricesEvolution(m_upReality->GetLastMarketRef());
}

double pca::CPriceCalculator::GetDesiredProdAmount(std::string sPerson, std::string sProductName)
{
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);
    CProduct* pProductRef = m_upReality->GetProduct(sProductName);

    if (pPersonRef)
    {
        return pPersonRef->GetDesiredProdAmount(pProductRef);
    }

    return 0.0;

}

void pca::CPriceCalculator::PrintPersonOptionAdjustmentToFile(std::string sPerson)
{
    CPerson* pPersonRef = m_upReality->GetLastMarketRef()->GetPersonRef(sPerson);

    if (pPersonRef)
    {
        pca::CUtils::PrintPersonOptionAdjustmentToFile(pPersonRef);        
    }
}

void pca::CPriceCalculator::PrintPersonsOptionAdjustmentToFile()
{
    if (m_upReality->GetLastMarketRef())
        pca::CUtils::PrintPersonsOptionAdjustmentToFile(m_upReality->GetLastMarketRef());
}

