#include "Prices.h"

pca::CPrices::CPrices()
{
    //ctor
}

pca::CPrices::~CPrices()
{
    //dtor
}

void pca::CPrices::IncreasePrice(int nProductId, double dAmount)
{
    if(m_mapProd_Price.end()==m_mapProd_Price.find(nProductId))
    {
        m_mapProd_Price[nProductId]=dAmount;
    }
    else
    {
        m_mapProd_Price[nProductId] += dAmount;
    }

}

void pca::CPrices::DecreasePrice(int nProductId, double dAmount)
{
    IncreasePrice(nProductId,-dAmount);
}
