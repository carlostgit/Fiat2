#ifndef CPRICESLOGINFO_H
#define CPRICESLOGINFO_H

#include <vector>
#include <map>
#include <memory>

namespace pca
{
    class CProduct;
    class CProductPriceAdjustmentInfo;
    class CPrices;
    class CMarket;

    class CPricesLogInfo
    {
    public:
        CPricesLogInfo(pca::CMarket* pMarketRef);
        virtual ~CPricesLogInfo();

        void AddPriceChangeStepToVector(double dValueArg);
        void ResetLastPrices();
        void RegisterPrices();
        bool ArePricesEvolving();
        std::map<pca::CProduct*, std::vector<double> > GetProductPrices();
        std::map<pca::CProduct*, std::vector<double> > GetProductAllPrices();        
        std::vector<double> GetAllPriceChangeStepsVector();
        std::map<pca::CProduct*, std::vector<long> > GetProductPriceTops();
        std::map<pca::CProduct*, std::vector<long> > GetProductPriceBottoms();

    protected:
        
    private:

        std::map<CProduct*, std::unique_ptr<CProductPriceAdjustmentInfo> > m_mapProduct_AdjustmentInfo;
        std::vector<double> m_vPriceChangeStepsVector;

        pca::CPrices* m_pPricesRef = nullptr;
        pca::CMarket* m_pMarketRef = nullptr;
 
    };
}

#endif // CPRICESLOGINFO_H
