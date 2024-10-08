#include "Prices.h"
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include "Market.h"
#include <assert.h>

pca::CPrices::CPrices(pca::CMarket* pMarketRef)
{
    m_pMarketRef = pMarketRef;
    //ctor
    
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
    //for (auto& pProduct : pca::CReality::GetProducts())
    for (auto& pProduct : m_pMarketRef->GetProducts())
    {
        m_mapProd_Price[pProduct] = 1.0;
    }

    //for (auto& pProduct : pca::CReality::GetProducts())
    for (auto& pProduct : m_pMarketRef->GetProducts())
    {
        SetCurrency(pProduct);
        break;
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

void pca::CPrices::SetPriceOfProduct(CProduct* pProduct, double dAmount)
{
    //auto vProducts = pca::CReality::GetProducts();
    auto vProducts = m_pMarketRef->GetProducts();
    if (vProducts.end() == std::find(vProducts.begin(), vProducts.end(), pProduct))
    {
        assert("" == "Este producto no existe!");
    }

    m_mapProd_Price[pProduct] = dAmount;
}

void pca::CPrices::SetCurrency(CProduct* pProduct)
{
    m_pCurrency = pProduct;
}



