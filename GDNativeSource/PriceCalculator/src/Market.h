#ifndef MARKET_H
#define MARKET_H

//#include "PriceCalculationDefines.h"
#include "Person.h"
#include <vector>
#include <memory>

namespace pca
{
    class CPrices;
    class CPricesLogInfo;

    

    class CMarket
    {
    public:

        friend class CTester;

        CMarket();
        virtual ~CMarket();

        CPrices* GetPricesRef() {
            return m_upPrices.get();
        }

        void AddPerson(std::unique_ptr<CPerson> upPerson);
        void RemovePerson(std::string sPersonArg);
        void RemovePerson(long nId);        

        void CalculateNewPrices();

    protected:
        std::map<pca::CProduct*, double> CalculateNewPricesIncrement(double dParamPriceChangeStepArg);

        void SetExcessProducts(std::map<pca::CProduct*, double> mapExcessProducts) {
            m_mapExcessProducts = mapExcessProducts;
        }

        bool ChangePrices(double dParamPriceChangeStepArg);
        void AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps);
        void CalculateSumOfTrade();
        void CalculateTradesWithCurrentBestCombinations();

    private:

        std::vector<std::unique_ptr<pca::CPerson>> m_vPersons;
        std::map<pca::CProduct*, double> m_mapSumOfTrade;
        std::map<pca::CProduct*, double> m_mapExcessProducts;

        std::unique_ptr<CPrices> m_upPrices;
        std::unique_ptr<CPricesLogInfo> m_upPricesLogInfo;

    };
}

#endif // MARKET_H
