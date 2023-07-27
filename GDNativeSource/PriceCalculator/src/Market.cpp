#include "Market.h"
#include "Person.h"

#include <iostream>
#include <iomanip>

pca::CMarket::CMarket()
{
    //ctor

}

pca::CMarket::~CMarket()
{
    //dtor
}

void pca::CMarket::AddPerson(std::unique_ptr<CPerson> upPerson)
{
    m_vPersons.push_back(std::move(upPerson));
}

void pca::CMarket::AdjustBestCombinations(double dBudgetStep, int nMaxNumSteps)
{
    for (auto& personRef : m_vPersons)
    {
        personRef->AdjustBestCombinationForPersonWithMaxNumSteps(dBudgetStep, nMaxNumSteps);
    }
}


//func _adjust_best_combinations(budget_step:float, max_num_steps : int) :
//	for person in _persons :
//#		if _person_best_combination_dict.has(person)==false:
//#			var empty_combidict : Dictionary = {}
//#			_person_best_combination_dict[person] = empty_combidict
//self.adjust_best_combination_for_person_with_max_num_steps(person, budget_step, max_num_steps)



//func _adjust_best_combinations(budget_step:float, max_num_steps : int) :
//    for person in _persons :
//#		if _person_best_combination_dict.has(person)==false:
//#			var empty_combidict : Dictionary = {}
//#			_person_best_combination_dict[person] = empty_combidict
//self.adjust_best_combination_for_person_with_max_num_steps(person, budget_step, max_num_steps)



//func adjust_best_combination_for_person_with_max_num_steps(person_arg:String, budget_step : float, max_num_steps : int)->Dictionary:
//if _person_owned_dict.has(person_arg) :
//	#		var combidict : Dictionary = _person_owned_dict[person_arg]
//	#		var budget : float = Prices.calculate_combidict_price(combidict)
//	##		print("Budget for " + person_arg + ": " + str(budget))
//	#		_person_value_of_owned[person_arg] = budget
//#
//	#		var budget : float = self.get_value_of_owned(person_arg)
//	if self._person_tradecalc.has(person_arg) :
//		var trade_calc : TradeCalculator = self._person_tradecalc[person_arg]
//
//		if _person_best_combination_dict.has(person_arg) == false :
//			var empty_combidict : Dictionary = {}
//			_person_best_combination_dict[person_arg] = empty_combidict
//			var current_best_combidict = _person_best_combination_dict[person_arg]
//			#			var best_combidict : Dictionary = trade_calc.adjust_best_combidict(budget, current_best_combidict_arg, budget_step, max_num_steps)
//			#			TODO : Probar adjust_best_combidict_changing_step
//			#			var init_budget_step = budget_step * 8
//			#			var best_combidict : Dictionary = trade_calc.adjust_best_combidict_changing_step(budget, current_best_combidict, init_budget_step, budget_step, max_num_steps)
//			#			_person_best_combination_dict[person_arg] = best_combidict
//#
//			var best_combidict : Dictionary = improve_combination(trade_calc, _person_owned_dict[person_arg], current_best_combidict, budget_step, max_num_steps)
//			_person_best_combination_dict[person_arg] = best_combidict
//			#			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
//			return best_combidict
//			var null_dictionary = {}
//			_person_best_combination_dict[person_arg] = null_dictionary
//			return null_dictionary

