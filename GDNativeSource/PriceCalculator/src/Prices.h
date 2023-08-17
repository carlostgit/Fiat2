#ifndef CPRICES_H
#define CPRICES_H

//#include "PriceCalculationDefines.h"

#include <map>

namespace pca
{
    class CProduct;
    class COption;

    class CPrices
    {
    public:
        CPrices();        
        virtual ~CPrices();

        void IncreasePrice(CProduct* pProductRef, double dPrice);
        void DecreasePrice(CProduct* pProductRef, double dPrice);

        //calculate_combidict_price(productdict)
        double CalculateCombidictPrice(std::map<CProduct*, double> mapProd_Amount);
        double GetPriceOfProduct(CProduct* pProdRef);

    protected:
        
        void InitDefaultPrices();

    private:

        std::map<CProduct*, double> m_mapProd_Price;
    };
}

#endif // CPRICES_H
