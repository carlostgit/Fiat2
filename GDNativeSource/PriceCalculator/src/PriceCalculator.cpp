#include "PriceCalculator.h"
#include "Person.h"
#include "Prices.h"
#include "Market.h"
#include "Reality.h"



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
