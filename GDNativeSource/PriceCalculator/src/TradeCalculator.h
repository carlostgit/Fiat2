#ifndef CTRADECALCULATOR_H
#define CTRADECALCULATOR_H

#include <map>


class CTradeCalculator
{
    public:
        CTradeCalculator();
        virtual ~CTradeCalculator();

        //func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
        std::map<int,double> AdjustBestCombidict(double dBudgetArg, std::map<int,double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg);

    protected:

    private:
};

#endif // CTRADECALCULATOR_H
