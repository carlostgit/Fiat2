#include "MarketTest.h"

#include <map>

std::map<int,double> g_map_Product_Price;
std::map<int,std::map<int,double> > g_map_Person_mapProdAmount;

void(*m_setPrice)(int nProduct, double dAmount)=0;

extern "C" double market_calculationTest(int i)
{
    double dI = static_cast<double>(i);
    dI += 1.5;

    return dI;
}



extern "C" void market_addPriceForProduct(int nProductId, double dPrice)
{
    g_map_Product_Price[nProductId]=dPrice;
}

extern "C" void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount)
{
    if(g_map_Person_mapProdAmount.end() == g_map_Person_mapProdAmount.find(nPersonId))
    {

        std::map<int,double> productAmount;
        productAmount[nProductId]=dAmount;
        g_map_Person_mapProdAmount[nPersonId] = productAmount;
    }
    else
        g_map_Person_mapProdAmount[nPersonId][nProductId]=dAmount;
}

extern "C" void market_setCallbackMethodForPrices(void(*setPrice)(int nProduct, double dAmount))
{
    m_setPrice = setPrice;

    if (g_map_Product_Price.empty())
        m_setPrice(1,1.2);
    else
    {
        int nFirstAmount = g_map_Product_Price.begin()->first;
        int nSecondAmount = g_map_Product_Price.begin()->second;
        m_setPrice(nFirstAmount,nSecondAmount);

    }


}
