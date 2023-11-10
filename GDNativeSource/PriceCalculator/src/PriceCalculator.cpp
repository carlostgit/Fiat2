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



pca::CPriceCalculator::CPriceCalculator()
{
    //ctor

    //std::vector<CPerson> myVector;
    //myVector.push_back(CPerson());

    //std::unique_ptr<CPerson> upNewPerson(new CPerson());
    //m_vpPersons.push_back(std::move(upNewPerson));
    //m_vpPersons.push_back(std::unique_ptr<CPerson>(new CPerson()));
}

pca::CPriceCalculator::~CPriceCalculator()
{
    //dtor
}

int pca::CPriceCalculator::GetTestPrice()
{
    return 8;
}


void pca::CPriceCalculator::CreateEmptyMarket()
{
    CReality::Init();
    m_upMarket.reset();
    std::unique_ptr<CMarket> upMarket(new CMarket());
    m_upMarket = std::move(upMarket);

    CReality::InitEmpty();
}

void pca::CPriceCalculator::CreateProduct(std::string sProductName)
{
    CReality::CreateProduct(sProductName);
}

void pca::CPriceCalculator::SetCurrency(std::string sProductName)
{
    if (nullptr == m_upMarket)
        return;

    CPrices* pPricesRef = m_upMarket->GetPricesRef();

    CProduct* pProductRef = CReality::GetProduct(sProductName);

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
    CProduct* pProductRef = CReality::GetProduct(sProduct);
    if (pProductRef)
    {
        CReality::CreateOption(sProduct, sOption);
    }
}

void pca::CPriceCalculator::AddToMarket_CreatePerson(std::string sPerson)
{
    if (m_upMarket)
        m_upMarket->CreatePerson(sPerson);
}

void pca::CPriceCalculator::AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount)
{
    if (nullptr == m_upMarket)
        return;

    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);
    CProduct* pProductRef = CReality::GetProduct(sProduct);

    if (pPersonRef && pProductRef)
    {
        pPersonRef->AddProductAmount(pProductRef, dAmount);
    }
}

void pca::CPriceCalculator::AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
{
    if (nullptr == m_upMarket)
        return;

    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);
    COption* pOptionRef = CReality::GetOption(sOption);

    if (pPersonRef && pOptionRef)
    {
        pca::CSatisfactionCalculator* pSatCalculator = pPersonRef->GetTradeCalculatorRef()->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pOptionRef, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pOptionRef, dMaxValue);        
    }
}

void pca::CPriceCalculator::AdjustPrices()
{
    if (m_upMarket)
        m_upMarket->CalculateNewPrices();

}
bool pca::CPriceCalculator::IsProduct(std::string sProductName)
{
    CProduct* pProductRef = CReality::GetProduct(sProductName);

    if (pProductRef)
    {
        return true;
    }

    return false;
}

bool pca::CPriceCalculator::IsPerson(std::string sPersonName)
{
    if (nullptr == m_upMarket)
        return false;

    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPersonName);

    if (pPersonRef)
    {
        return true;
    }

    return false;
}

bool pca::CPriceCalculator::IsOption(std::string sOptionName)
{
    COption* pOptionRef = CReality::GetOption(sOptionName);

    if (pOptionRef)
    {
        return true;
    }

    return false;
}

std::string pca::CPriceCalculator::GetCurrency()
{
    if (m_upMarket && m_upMarket->GetPricesRef() && m_upMarket->GetPricesRef()->GetCurrency())
    {
        return m_upMarket->GetPricesRef()->GetCurrency()->GetName();
    }
    return "";
}

double pca::CPriceCalculator::GetPrice(std::string sProductName)
{
    CProduct* pProductRef = CReality::GetProduct(sProductName);

    if (m_upMarket && m_upMarket->GetPricesRef() && pProductRef)
    {
        return m_upMarket->GetPricesRef()->GetPriceOfProduct(pProductRef);
    }

    return 0.0;
}

double pca::CPriceCalculator::GetProductAmount(std::string sProductName, std::string sPerson)
{
    CProduct* pProductRef = CReality::GetProduct(sProductName);
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);

    if (pPersonRef && pProductRef)
    {
        return pPersonRef->GetOwnedProdAmount(pProductRef);
    }

    return 0.0;

}

double pca::CPriceCalculator::GetOptionAmount(std::string sOptionName, std::string sPerson)
{
    COption* pOptionRef = CReality::GetOption(sOptionName);
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);

    if (pPersonRef && pOptionRef)
    {
        return pPersonRef->GetCurrentOptAmount(pOptionRef);
    }

    return 0.0;

}

void pca::CPriceCalculator::PrintPricesEvolution()
{
    CUtils::PrintPricesEvolution(m_upMarket.get());
}

double pca::CPriceCalculator::GetDesiredProdAmount(std::string sPerson, std::string sProductName)
{
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);
    CProduct* pProductRef = CReality::GetProduct(sProductName);

    if (pPersonRef)
    {
        return pPersonRef->GetDesiredProdAmount(pProductRef);
    }

    return 0.0;

}

void pca::CPriceCalculator::PrintPersonOptionAdjustmentToFile(std::string sPerson)
{
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);

    if (pPersonRef)
    {
        pca::CUtils::PrintPersonOptionAdjustmentToFile(pPersonRef);        
    }
}

void pca::CPriceCalculator::PrintPersonsOptionAdjustmentToFile()
{
    if (m_upMarket)
        pca::CUtils::PrintPersonsOptionAdjustmentToFile(m_upMarket.get());
}

