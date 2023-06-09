#include "Prices.h"
#include "PriceCalculationDefines.h"
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
    for (auto& nOption : c_setProducts)
    {
        m_mapProd_Price[nOption] = 1.0;
    }
}

void pca::CPrices::IncreasePrice(eProd nProductId, double dAmount)
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

void pca::CPrices::DecreasePrice(eProd nProductId, double dAmount)
{
    IncreasePrice(nProductId,-dAmount);
}

double pca::CPrices::CalculateCombidictPrice(std::map<eProd, double> mapProd_Amount)
{
    double dTotalPrice = 0.0;

    for (auto& pairProd_Amount : mapProd_Amount)
    {
        eProd nProd = pairProd_Amount.first;

        if (m_mapProd_Price.end() == m_mapProd_Price.find(nProd))
        {
            assert("" == "Producto sin precio en pca::CPrices::CalculateCombidictPrice");
        }
        else
        {
            double dAmount = pairProd_Amount.second;
            double dPrice = this->m_mapProd_Price[nProd];

            dTotalPrice += dAmount*dPrice;
        }
    }
    
    return dTotalPrice;
}

double pca::CPrices::GetPriceOfProduct(eProd nProd)
{
    if (m_mapProd_Price.end() == m_mapProd_Price.find(nProd))
    {
        assert("" == "Producto sin precio en pca::CPrices::CalculateCombidictPrice");
        return 0.0;
    }
    else
    {        
        double dPrice = this->m_mapProd_Price[nProd];
        return dPrice;
    }
}

