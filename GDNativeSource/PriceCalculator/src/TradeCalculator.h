#ifndef CTRADECALCULATOR_H
#define CTRADECALCULATOR_H

#include <map>
#include <memory>


namespace pca
{
    class CSatisfactionCalculator;

    class CTradeCalculator
    {
    public:
        CTradeCalculator();
        virtual ~CTradeCalculator();

        //func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
        std::map<int, double> AdjustBestCombidict(double dBudgetArg, std::map<int, double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg);

    protected:

    private:

        std::unique_ptr<CSatisfactionCalculator> m_pSatisfactionCalculator;
    };

}

#endif // CTRADECALCULATOR_H
