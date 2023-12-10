#ifndef CTRADECALCULATOR_H
#define CTRADECALCULATOR_H

//#include "PriceCalculationDefines.h"

#include <map>
#include <memory>


namespace pca
{
    class CSatisfactionCalculator;
    class CPrices;
    class COption;
    class CProduct;
    class CMarket;

    class CTradeCalculator
    {
    public:
        CTradeCalculator(std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator, CPrices* pPricesRef, CMarket* pMarketRef);

        virtual ~CTradeCalculator();

        //func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
        std::map<pca::COption*, double> AdjustBestCombidict(double dBudgetArg, std::map<COption*, double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg);
        std::map<pca::COption*, double> AdjustBestCombidictChangingStep(double dBudgetArg, std::map<COption*, double> mapCurrentCombidict, double dInitBudgetStepArg, double dTargetBudgetStepArg, int nMaxStepArg);
        std::map<pca::COption*, double> ImproveCombination(std::map<CProduct*, double> mapOwnedCombidictArg, std::map<COption*, double> mapCurrentBestCombidictArg, double dInitBudgetStep, double dTargetBudgetStep, int nMaxNumSteps);

        pca::CSatisfactionCalculator* GetSatisfactionCalculatorRef();

    protected:

    private:

        std::unique_ptr<CSatisfactionCalculator> m_upSatisfactionCalculator;
        CPrices* m_pPricesRef = nullptr;
        CMarket* m_pMarketRef = nullptr;

    };

}

#endif // CTRADECALCULATOR_H
