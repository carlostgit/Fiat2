#include "PriceCalculator.h"
#include "Person.h"
#include "Prices.h"
#include "Market.h"


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
