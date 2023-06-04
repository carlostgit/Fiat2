#ifndef CPRICES_H
#define CPRICES_H

#include <map>

namespace pca
{
    class CPrices
    {
    public:
        CPrices();        
        virtual ~CPrices();

        void IncreasePrice(int nProductId, double dPrice);
        void DecreasePrice(int nProductId, double dPrice);

        //calculate_combidict_price(productdict)
        double CalculateCombidictPrice(std::map<int, double> mapProd_Amount);
        double GetPriceOfProduct(long nProd);

    protected:
        
        void InitDefaultPrices();

    private:

        std::map<int, double> m_mapProd_Price;
    };
}

#endif // CPRICES_H
