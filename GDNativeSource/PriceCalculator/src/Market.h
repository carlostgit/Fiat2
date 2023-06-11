#ifndef MARKET_H
#define MARKET_H

#include "PriceCalculationDefines.h"
#include "Person.h"
#include <vector>

namespace pca
{
    class CMarket
    {
    public:
        CMarket();
        virtual ~CMarket();

        void AddPersonRef(CPerson* pPersonRef);

        void AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps);


    protected:

    private:

        std::vector<pca::CPerson*> m_vPersonRefs;

    };
}

#endif // MARKET_H
