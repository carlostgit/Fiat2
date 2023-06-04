#include "Person.h"
#include "PriceCalculationDefines.h"

pca::CPerson::CPerson()
{
    //ctor
    InitDefaultAmounts();
}

pca::CPerson::~CPerson()
{
    //dtor
}

void pca::CPerson::InitDefaultAmounts()
{
    for (auto& nProduct : c_setProducts)
    {
        m_mapOwnedProd_Amount[nProduct] = 1.0;
    }
}

void pca::CPerson::AddProductAmount(int nProductId, double dAmount)
{
    if(m_mapOwnedProd_Amount.end()==m_mapOwnedProd_Amount.find(nProductId))
    {
        m_mapOwnedProd_Amount[nProductId]=dAmount;
    }
    else
    {
        m_mapOwnedProd_Amount[nProductId] += dAmount;
    }
}

void pca::CPerson::RemoveProductAmount(int nProductId, double dAmount)
{
    AddProductAmount(nProductId, -dAmount);
}
