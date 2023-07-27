#ifndef MARKET_H
#define MARKET_H

#include "PriceCalculationDefines.h"
#include "Person.h"
#include <vector>
#include <memory>

namespace pca
{
    class CMarket
    {
    public:
        CMarket();
        virtual ~CMarket();

        void AddPerson(std::unique_ptr<CPerson> upPerson);

        void AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps);


    protected:

    private:

        std::vector<std::unique_ptr<pca::CPerson>> m_vPersons;

    };
}

#endif // MARKET_H
