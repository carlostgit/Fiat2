#ifndef CPRICES_H
#define CPRICES_H

//#include "PriceCalculationDefines.h"

#include <map>

namespace pca
{
    class CProduct;
    class COption;
    class CMarket;

    class CPrices
    {
    public:
        CPrices(pca::CMarket* pMarketRef);
        virtual ~CPrices();

        void IncreasePrice(CProduct* pProductRef, double dPrice);
        void DecreasePrice(CProduct* pProductRef, double dPrice);

        //calculate_combidict_price(productdict)
        double CalculateCombidictPrice(std::map<CProduct*, double> mapProd_Amount);
        double GetPriceOfProduct(CProduct* pProdRef);
        void SetPriceOfProduct(CProduct* pProduct, double dAmount);
        
        void SetCurrency(CProduct* pProduct);
        CProduct* GetCurrency() { 
            return m_pCurrency; 
        }
        bool IsCurrency(CProduct* pProduct) {
            if (m_pCurrency == pProduct)
                return true;
            else
                return false;
        }

        CMarket* GetMarketRef() {
            return m_pMarketRef;
        }

    protected:
        
        void InitDefaultPrices();

    private:

        std::map<CProduct*, double> m_mapProd_Price;
        CProduct* m_pCurrency = nullptr;

        pca::CMarket* m_pMarketRef = nullptr;
    };
}

#endif // CPRICES_H
