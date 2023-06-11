#ifndef CPERSON_H
#define CPERSON_H

#include "PriceCalculationDefines.h"
#include <map>

namespace pca
{
    class CPrices;
    class CMarket;
    class CTradeCalculator;

    class CPerson
    {
    public:
        CPerson(CPrices* pPricesRef, CMarket* pMarketRef, CTradeCalculator* pTradCalculatorRef);
        virtual ~CPerson();

        void AddProductAmount(eProd nProductId, double dAmount);
        void RemoveProductAmount(eProd nProductId, double dAmount);

        void AdjustBestCombinationForPerson();
        std::map<pca::eOpt, double> AdjustBestCombinationForPersonWithMaxNumSteps(double dBudgetStepArg, int nMaxNumSteps);
        //func adjust_best_combination_for_person(person_arg:String) :
        //    var budget_step = 0.01
        //    var max_num_steps = 5
        //    adjust_best_combination_for_person_with_max_num_steps(person_arg, budget_step, max_num_steps)



    protected:

        void InitDefaultAmounts();

    private:

        std::map<pca::eProd, double> m_mapOwnedProd_Amount;
        std::map<pca::eOpt, double> m_mapCurrentOpt_Amount;

        CPrices* m_pPricesRef = nullptr;
        CMarket* m_pMarketRef = nullptr;
        CTradeCalculator* m_pTradeCalculatorRef = nullptr;

    };
}
#endif // CPERSON_H
