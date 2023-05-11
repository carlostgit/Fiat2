#include "TradeCalculator.h"

#include <iostream>

CTradeCalculator::CTradeCalculator()
{
    //ctor
}

CTradeCalculator::~CTradeCalculator()
{
    //dtor
}


//TODO: Pasar este método a C++
std::map<int,double> CTradeCalculator::AdjustBestCombidict(double dBudgetArg, std::map<int,double> map_nOption_dAmount, double dBudgetStepArg, int nMaxStepArg)
{
    std::map<int,double> mapCalculatedCombidict;

    std::cout << "TODO: AdjustBestCombidict" << std::endl;

    return mapCalculatedCombidict;
}

//func adjust_best_combidict(budget_arg:float, current_combidict:Dictionary, budget_step_arg, max_step_arg:int):
//#	TDOO: Hacer un método que llame a este método con pasos decrecientes en tamaño
//#	var new_combidict:Dictionary = current_combidict
//
//#	var best_combination:Dictionary = {}
//	var budget_step_length:float = budget_step_arg
//
//#	var products:Array = Prices.get_products()
//	var options:Array = _satisfaction_calculator.get_options()
//
//#	var combination:Dictionary = {}
//	var combination:Dictionary = current_combidict
//#	for option in options:
//#		combination[option] = 0
//
//	var productdict = _satisfaction_calculator.calculate_productdict_from_optiondict(combination)
//	var cost_of_arg_combination = Prices.calculate_combidict_price(productdict)
//
//	var left_money:float = budget_arg - cost_of_arg_combination
//
//#	var best_previous_satisfaction = combination
//	var best_previous_satisfaction:float = _satisfaction_calculator.calculate_satisf_of_combidict(combination)
//#	var best_previous_combination:Dictionary = combination
//
//	while left_money < 0:
//
//		var change_made:bool = false
//#		eliminaré productos en orden de menor reducción de satisfacción
//		var best_decrement_of_satisfaction = best_previous_satisfaction
//		var best_trying_combination = combination.duplicate()
//
//		for option_to_remove in options:
//			var product_to_remove = _satisfaction_calculator.get_product_from_option(option_to_remove)
//			var trying_combination_removing_product:Dictionary = combination.duplicate()
//			var remove_product_step = budget_step_length/Prices.get_price_of_product(product_to_remove)
//			if trying_combination_removing_product.has(option_to_remove)==false:
//				trying_combination_removing_product[option_to_remove] = 0
//			trying_combination_removing_product[option_to_remove] -= remove_product_step
//			if trying_combination_removing_product[option_to_remove]<0:
//				continue
//			var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination_removing_product)
//			var curent_decrement_of_satisfaction:float = best_previous_satisfaction - satisfaction_of_trying_combination
//
//
//			if  curent_decrement_of_satisfaction <= best_decrement_of_satisfaction:
//				best_trying_combination = trying_combination_removing_product
//				change_made = true
//
//				best_previous_satisfaction = satisfaction_of_trying_combination
//
//		if true == change_made:
//			combination = best_trying_combination
//			var current_left_money:float = left_money + budget_step_length
//			left_money = current_left_money
//
//		if false==change_made:
//			print ("Exited adjust_best_combidict because no option to remove found")
//			break
//
//
//
//	if left_money >= 0:
//#		Ya no se puede añadir ningún producto, pero puede que quede dinero para intercambiar productos
//		var count:int = 0
//		while true:
//			count += 1
//			if count>max_step_arg:
//#				print ("Exited adjust_best_combidict because too many iterations are being used")
//				break
//
//			var change_made = false
//			for new_option in options:
//				var new_product = _satisfaction_calculator.get_product_from_option(new_option)
//				var new_product_step = budget_step_length/Prices.get_price_of_product(new_product)
//
//				var trying_combination_adding_product:Dictionary = combination.duplicate()
//				if trying_combination_adding_product.has(new_option)==false:
//					trying_combination_adding_product[new_option]=0
//				trying_combination_adding_product[new_option] += new_product_step
//				var current_left_money = left_money-budget_step_length
//
//				if (current_left_money < 0.0):
//					for old_option in options:
//						if new_option!=old_option:
//							var old_product = _satisfaction_calculator.get_product_from_option(old_option)
//							var old_product_step = budget_step_length/Prices.get_price_of_product(old_product)
//							if combination[old_option]>=old_product_step:
//								var trying_combination_swapping_products:Dictionary = trying_combination_adding_product.duplicate()
//								if trying_combination_swapping_products.has(old_option)==false:
//									trying_combination_swapping_products[old_option]=0
//								trying_combination_swapping_products[old_option] -= old_product_step
//								current_left_money = left_money
//
//								var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination_swapping_products)
//
//								var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
//
//								if  increment_of_satisfaction > 0.0:
//									combination = trying_combination_swapping_products
//									change_made = true
//									left_money = current_left_money
//									best_previous_satisfaction = satisfaction_of_trying_combination
//									break
//
//				else:
//
//					var satisfaction_of_trying_combination:float = _satisfaction_calculator.calculate_satisf_of_combidict(trying_combination_adding_product)
//
//					var increment_of_satisfaction:float = satisfaction_of_trying_combination - best_previous_satisfaction
//
//					if  increment_of_satisfaction > 0.0:
//						combination = trying_combination_adding_product
//						change_made = true
//						left_money = current_left_money
//						best_previous_satisfaction = satisfaction_of_trying_combination
//
//			if false==change_made:
//				break
//
//	return combination

























