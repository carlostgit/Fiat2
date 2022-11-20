#include "Prices.h"

CPrices::CPrices()
{
    //ctor
}

CPrices::~CPrices()
{
    //dtor
}

void CPrices::IncreasePrice(int nProductId, double dAmount)
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

void CPrices::DecreasePrice(int nProductId, double dAmount)
{
    IncreasePrice(nProductId,-dAmount);
}
