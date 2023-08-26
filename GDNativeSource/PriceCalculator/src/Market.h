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
        CMarket();
        virtual ~CMarket();

        void AddPerson(std::unique_ptr<CPerson> upPerson);
        void RemovePerson(std::string sPersonArg);
        void RemovePerson(long nId);

        void AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps);

        void CalculateTradesWithCurrentBestCombinations();
        void CalculateSumOfTrade();

        void CalculateNewPrices();

        bool ChangePrices(double dParamPriceChangeStepArg);

        std::map<CProduct*, double> CalculateNewPricesIncrement(double dParamPriceChangeStepArg);

    protected:

    private:

        std::vector<std::unique_ptr<pca::CPerson>> m_vPersons;        
        std::map<pca::CProduct*, double> m_mapSumOfTrade;
        std::map<pca::CProduct*, double> m_mapExcessProducts;        

        std::unique_ptr<CPrices> m_upPrices;
        std::unique_ptr<CPricesLogInfo> m_upPricesLogInfo;

    };
}

#endif // MARKET_H
