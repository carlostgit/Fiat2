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
        CTradeCalculator(std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator, CPrices* pPricesRef);

        virtual ~CTradeCalculator();

        //func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
        std::map<pca::eOpt, double> AdjustBestCombidict(double dBudgetArg, std::map<eOpt, double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg);
        std::map<pca::eOpt, double> AdjustBestCombidictChangingStep(double dBudgetArg, std::map<eOpt, double> mapCurrentCombidict, double dInitBudgetStepArg, double dTargetBudgetStepArg, int nMaxStepArg);
        std::map<pca::eOpt, double> ImproveCombination(std::map<eProd, double> mapOwnedCombidictArg, std::map<eOpt, double> mapCurrentBestCombidictArg, double dBudgetStep, int nMaxNumSteps);

    protected:

    private:

        std::unique_ptr<CSatisfactionCalculator> m_upSatisfactionCalculator;
        CPrices* m_pPricesRef = nullptr;

    };

}

#endif // CTRADECALCULATOR_H
