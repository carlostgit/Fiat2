#include "Person.h"
#include "PriceCalculationDefines.h"
#include "Prices.h"
#include "Market.h"
#include "TradeCalculator.h"


long pca::CPerson::ms_nId = 0;

pca::CPerson::CPerson(CPrices* pPricesRef, CMarket* pMarketRef, CTradeCalculator* pTradeCalculatorRef)
{
    ms_nId++;
    m_nId = ms_nId;

    m_pPricesRef = pPricesRef;
    m_pMarketRef = pMarketRef;
    m_pTradeCalculatorRef = pTradeCalculatorRef;

    //ctor
    InitDefaultAmounts();
}

pca::CPerson::~CPerson()
{
    //dtor
}

void pca::CPerson::InitDefaultAmounts()
{
    for (auto& nProduct : c_setProducts)
    {
        m_mapOwnedProd_Amount[nProduct] = 0.0;
    }
}

void pca::CPerson::AddProductAmount(eProd nProductId, double dAmount)
{
    if(m_mapOwnedProd_Amount.end()==m_mapOwnedProd_Amount.find(nProductId))
    {
        m_mapOwnedProd_Amount[nProductId]=dAmount;
    }
    else
    {
        m_mapOwnedProd_Amount[nProductId] += dAmount;
    }
}

void pca::CPerson::RemoveProductAmount(eProd nProductId, double dAmount)
{
    AddProductAmount(nProductId, -dAmount);
}

void pca::CPerson::AdjustBestCombinationForPerson()
{
    double dBudgetStep = 0.01;
    int nMaxNumSteps = 5;
    AdjustBestCombinationForPersonWithMaxNumSteps(dBudgetStep,nMaxNumSteps);
}
//func adjust_best_combination_for_person(person_arg:String) :
//    var budget_step = 0.01
//    var max_num_steps = 5
//    adjust_best_combination_for_person_with_max_num_steps(person_arg, budget_step, max_num_steps)


std::map<pca::eOpt, double> pca::CPerson::AdjustBestCombinationForPersonWithMaxNumSteps(double dBudgetStepArg, int nMaxNumStepsArg)
{
    m_pPricesRef->CalculateCombidictPrice(m_mapOwnedProd_Amount);
    std::map<pca::eOpt, double> mapBestCombidict = m_pTradeCalculatorRef->ImproveCombination(m_mapOwnedProd_Amount, m_mapCurrentOpt_Amount, dBudgetStepArg, nMaxNumStepsArg);

    this->m_mapCurrentOpt_Amount = mapBestCombidict;

    return mapBestCombidict;
}

// 
//    func adjust_best_combination_for_person_with_max_num_steps(person_arg:String, budget_step : float, max_num_steps : int)->Dictionary:
//    if _person_owned_dict.has(person_arg) :
//        #		var combidict : Dictionary = _person_owned_dict[person_arg]
//        #		var budget : float = Prices.calculate_combidict_price(combidict)
//        ##		print("Budget for " + person_arg + ": " + str(budget))
//        #		_person_value_of_owned[person_arg] = budget
//#
//        #		var budget : float = self.get_value_of_owned(person_arg)
//        if self._person_tradecalc.has(person_arg) :
//            var trade_calc : TradeCalculator = self._person_tradecalc[person_arg]
//
//            if _person_best_combination_dict.has(person_arg) == false :
//                var empty_combidict : Dictionary = {}
//                _person_best_combination_dict[person_arg] = empty_combidict
//                var current_best_combidict = _person_best_combination_dict[person_arg]
//                #			var best_combidict : Dictionary = trade_calc.adjust_best_combidict(budget, current_best_combidict_arg, budget_step, max_num_steps)
//                #			TODO : Probar adjust_best_combidict_changing_step
//                #			var init_budget_step = budget_step * 8
//                #			var best_combidict : Dictionary = trade_calc.adjust_best_combidict_changing_step(budget, current_best_combidict, init_budget_step, budget_step, max_num_steps)
//                #			_person_best_combination_dict[person_arg] = best_combidict
//#
//                var best_combidict : Dictionary = improve_combination(trade_calc, _person_owned_dict[person_arg], current_best_combidict, budget_step, max_num_steps)
//                _person_best_combination_dict[person_arg] = best_combidict
//                #			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
//                return best_combidict
//                var null_dictionary = {}
//                _person_best_combination_dict[person_arg] = null_dictionary
//                return null_dictionary


