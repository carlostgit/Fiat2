#ifndef CTRADECALCULATOR_H
#define CTRADECALCULATOR_H

#include "PriceCalculationDefines.h"

#include <map>
#include <memory>


namespace pca
{
    class CSatisfactionCalculator;
    class CPrices;

    class CTradeCalculator
    {
    public:
        CTradeCalculator(CSatisfactionCalculator* pSatisfactionCalculatorRef, CPrices* pPricesRef);

        virtual ~CTradeCalculator();

        //func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
        std::map<pca::eOpt, double> AdjustBestCombidict(double dBudgetArg, std::map<eOpt, double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg);

    protected:

    private:

        CSatisfactionCalculator* m_pSatisfactionCalculatorRef = nullptr;
        CPrices* m_pPricesRef = nullptr;

    };

}

#endif // CTRADECALCULATOR_H
