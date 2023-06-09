#ifndef CPRICES_H
#define CPRICES_H

#include "PriceCalculationDefines.h"

#include <map>

namespace pca
{
    class CPrices
    {
    public:
        CPrices();        
        virtual ~CPrices();

        void IncreasePrice(eProd nProductId, double dPrice);
        void DecreasePrice(eProd nProductId, double dPrice);

        //calculate_combidict_price(productdict)
        double CalculateCombidictPrice(std::map<eProd, double> mapProd_Amount);
        double GetPriceOfProduct(eProd nProd);

    protected:
        
        void InitDefaultPrices();

    private:

        std::map<eProd, double> m_mapProd_Price;
    };
}

#endif // CPRICES_H
