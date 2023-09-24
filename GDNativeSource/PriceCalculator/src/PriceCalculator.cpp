#include "PriceCalculator.h"
#include "Person.h"
#include "Prices.h"
#include "Market.h"
#include "Reality.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"



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
    CPrices* pPricesRef = m_upMarket->GetPricesRef();

    CProduct* pProductRef = CReality::GetProduct(sProductName);

    if (pPricesRef && pProductRef)
    {
        if (pPricesRef->IsCurrency(pProductRef))
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
    m_upMarket->CreatePerson(sPerson);
}

void pca::CPriceCalculator::AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount)
{
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);
    CProduct* pProductRef = CReality::GetProduct(sProduct);

    if (pPersonRef && pProductRef)
    {
        pPersonRef->AddProductAmount(pProductRef, dAmount);
    }
}

void pca::CPriceCalculator::AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
{
    CPerson* pPersonRef = m_upMarket->GetPersonRef(sPerson);
    COption* pOptionRef = CReality::GetOption(sOption);

    if (pPersonRef && pOptionRef)
    {
        pca::CSatisfactionCalculator* pSatCalculator = pPersonRef->GetTradeCalculatorRef()->GetSatisfactionCalculatorRef();
        pSatCalculator->SetPreferenceAt0(pOptionRef, dValueAt0);
        pSatCalculator->SetMaximumSatisf(pOptionRef, dMaxValue);        
    }
}
