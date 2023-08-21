#ifndef CPRODUCTPRICEADJUSTMENTINFO_H
#define CPRODUCTPRICEADJUSTMENTINFO_H

#include <limits>
#include <vector>

namespace pca
{

    class CProductPriceAdjustmentInfo
    {
    public:
        CProductPriceAdjustmentInfo();
        virtual ~CProductPriceAdjustmentInfo();

        void Reset();
        bool ArePricesChanging();
        std::vector<double> GetPrices();
        std::vector<double> GetAllPrices();
        void ResetLastPrices();
        void AddPriceIteration(double dPriceArg);
        std::vector<long> GetNumPriceTopsArray();
        std::vector<long> GetNumPriceBottomsArray();
        long GetNumPriceTops();
        long GetNumPriceBottoms();
        long CalculateNumPriceTops();
        long CalculateNumPriceBottoms();

    protected:
        
    private:

        const long m_nParamIterationsLog = 10;
        long m_nIteration = 0;
        double m_dMinPrice = std::numeric_limits<double>::max();
        double m_dMaxPrice = 0.0;
        
        std::vector<double> m_vLastPrices;
        std::vector<double> m_vAllPrices;

        std::vector<long> m_vNumLastPriceTops;
        std::vector<long> m_vNumLastPriceBottoms;

    };
}

#endif // CPRODUCTPRICEADJUSTMENTINFO_H
