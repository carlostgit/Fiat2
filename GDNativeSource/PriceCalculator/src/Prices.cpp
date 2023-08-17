#include "Prices.h"
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include <assert.h>

pca::CPrices::CPrices()
{
    //ctor
    //TODO:
    InitDefaultPrices();
}

pca::CPrices::~CPrices()
{
    //dtor
}

void pca::CPrices::InitDefaultPrices()
{
    //Inicializo los precios a 1.0
    //for (auto& nOption : c_setProducts)
    for (auto& nOption : pca::CReality::GetProducts())
    {
        m_mapProd_Price[nOption] = 1.0;
    }
}

void pca::CPrices::IncreasePrice(CProduct* pProductRef, double dAmount)
{
    if(m_mapProd_Price.end()==m_mapProd_Price.find(pProductRef))
    {
        m_mapProd_Price[pProductRef]=dAmount;
    }
    else
    {
        m_mapProd_Price[pProductRef] += dAmount;
    }

}

void pca::CPrices::DecreasePrice(CProduct* pProductRef, double dAmount)
{
    IncreasePrice(pProductRef,-dAmount);
}

double pca::CPrices::CalculateCombidictPrice(std::map<CProduct*, double> mapProd_Amount)
{
    double dTotalPrice = 0.0;

    for (auto& pairProd_Amount : mapProd_Amount)
    {
        CProduct* pProd = pairProd_Amount.first;

        if (m_mapProd_Price.end() == m_mapProd_Price.find(pProd))
        {
            assert("" == "Producto sin precio en pca::CPrices::CalculateCombidictPrice");
        }
        else
        {
            double dAmount = pairProd_Amount.second;
            double dPrice = this->m_mapProd_Price[pProd];

            dTotalPrice += dAmount*dPrice;
        }
    }
    
    return dTotalPrice;
}

double pca::CPrices::GetPriceOfProduct(CProduct* pProdRef)
{
    if (m_mapProd_Price.end() == m_mapProd_Price.find(pProdRef))
    {
        assert("" == "Producto sin precio en pca::CPrices::CalculateCombidictPrice");
        return 0.0;
    }
    else
    {        
        double dPrice = this->m_mapProd_Price[pProdRef];
        return dPrice;
    }
}

