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

    protected:
        void IncreasePrice(int nProductId, double dPrice);
        void DecreasePrice(int nProductId, double dPrice);

    private:

        std::map<int, double> m_mapProd_Price;
    };
}

#endif // CPRICES_H
