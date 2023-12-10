#include "TradeCalculator.h"

#include <iostream>
#include <set>
//#include "PriceCalculationDefines.h"
#include "Reality.h"
#include "SatisfactionCalculator.h"
#include "Prices.h"
#include "Utils.h"
#include "Option.h"
#include "Market.h"

#include <assert.h>

const bool c_traces = false;

pca::CTradeCalculator::CTradeCalculator(std::unique_ptr<CSatisfactionCalculator> upSatisfactionCalculator, CPrices* pPricesRef, CMarket* pMarketRef)
{
    //ctor
    m_upSatisfactionCalculator = std::move(upSatisfactionCalculator);
    m_pPricesRef = pPricesRef;
    m_pMarketRef = pMarketRef;
}

pca::CTradeCalculator::~CTradeCalculator()
{
    //dtor
}


//TODO: Pasar este método a C++
//Habrá que cambiar este método para que quede claro que la combinación que se ajusta es de opciones
std::map<pca::COption* ,double> pca::CTradeCalculator::AdjustBestCombidict(double dBudgetArg, std::map<COption*,double> mapCurrentCombidictArg, double dBudgetStepArg, int nMaxStepArg)
{
    //TODO: Hacer una clase que permita imprimir bien el contenido de elementos como std::map<int,double> mapCurrentCombidict

    if (c_traces) std::cout << "Start of AdjustBestCombidict" << std::endl;

    if (c_traces) std::cout << "dBudgetArg: " << dBudgetArg << " dBudgetStepArg: " << dBudgetStepArg << " nMaxStepArg: " << nMaxStepArg << std::endl;


    if (nullptr == m_upSatisfactionCalculator || nullptr == m_pPricesRef)
    {
        assert(""=="Falta m_pSatisfactionCalculatorRef");
        assert(""=="Falta m_pPricesRef");
        return mapCurrentCombidictArg;
    }

    double dBudgetStepLength = dBudgetStepArg;
    //std::set<eOpt> setOptions = c_setOptions;
    std::vector<COption*> vOptions = m_pMarketRef->GetOptions();
    std::map<COption*, double> mapCombination = mapCurrentCombidictArg;
    //std::map<eProd, double> mapProductDict = m_pSatisfactionCalculatorRef->CalculateProductdictFromOptiondict(mapCombination);
    std::map<CProduct*, double> mapProductDict = CUtils::CalculateProductdictFromOptiondict(mapCombination);

    double dCostOfArgCombination = m_pPricesRef->CalculateCombidictPrice(mapProductDict);
    double dLeftMoney = dBudgetArg - dCostOfArgCombination;

    double dBestPreviousSatisfaction = m_upSatisfactionCalculator->CalculateSatisfOfCombidict(mapCombination);

    if (c_traces) std::cout << "Starting with dLeftMoney: " << dLeftMoney << std::endl;
    if (c_traces) std::cout << "Starting with Satisfaction: " << dBestPreviousSatisfaction << std::endl;

    //Si el presupuesto no llega para la combinación actual, eliminamos elementos que sean relativamente caros y poco satisfactorios
    while (dLeftMoney < 0.0)
    {
        bool bChangeMade = false;
        //		Eliminaré productos en orden de menor reducción de satisfacción
        double dBestDecrementOfSatisfaction = dBestPreviousSatisfaction;
        std::map<COption*, double> mapBestTryingCombination = mapCombination;

        //for (auto& nOptionToRemove : c_setOptions)
        for (auto & pOptionToRemove : vOptions)
        {
            //CProduct* pProductToRemove = c_mapOption_Product.at(pOptionToRemove);
            CProduct* pProductToRemove = pOptionToRemove->GetProduct();
            std::map<COption*, double> mapTryingCombinationRemovingProduct = mapCombination;
            double dRemoveProductStep = dBudgetStepLength / m_pPricesRef->GetPriceOfProduct(pOptionToRemove->GetProduct());
            if (mapTryingCombinationRemovingProduct.end() == mapTryingCombinationRemovingProduct.find(pOptionToRemove))
            {
                //Igual habría que poner aquí un continue
                mapTryingCombinationRemovingProduct[pOptionToRemove] = 0.0;
            }

            mapTryingCombinationRemovingProduct[pOptionToRemove] -= dRemoveProductStep;

            if (mapTryingCombinationRemovingProduct[pOptionToRemove] < 0.0)
            {
                continue;
            }

            double dSatisfactionOfTryingCombination = m_upSatisfactionCalculator->CalculateSatisfOfCombidict(mapTryingCombinationRemovingProduct);
            double dCurentDecrementOfSatisfaction = dBestPreviousSatisfaction - dSatisfactionOfTryingCombination;

            if (dCurentDecrementOfSatisfaction <= dBestDecrementOfSatisfaction)
            {
                mapBestTryingCombination = mapTryingCombinationRemovingProduct;
                bChangeMade = true;
                dBestPreviousSatisfaction = dSatisfactionOfTryingCombination;
            }
        }

        if (true == bChangeMade)
        {
            mapCombination = mapBestTryingCombination;
            double dCurrentLeftMoney = dLeftMoney + dBudgetStepLength;
            dLeftMoney = dCurrentLeftMoney;

            if (c_traces) std::cout << "Element eliminated. dLeftMoney: " << dLeftMoney << std::endl;
            if (c_traces) std::cout << "Best previous Satisfaction: " << dBestPreviousSatisfaction << std::endl;
            if (c_traces) CUtils::PrintOptions(mapCombination);
        }

        if (false == bChangeMade)
        {
            if (c_traces) std::cout << "Exited adjust_best_combidict because no option to remove found" << std::endl;
            break;
        }
    }

    if (dLeftMoney >= 0)
    {
//#		Si ya no se puede añadir ningún producto, puede que quede dinero para intercambiar productos
        long nCount = 0;
        while (true)
        {
            nCount += 1;
            if (nCount> nMaxStepArg)
            {
                if (c_traces) std::cout << "Exited adjust_best_combidict because too many iterations are being used" << std::endl;
                break;
            }

            bool bChangeMade = false;
            //for (auto& nNewOption : c_setOptions)
            for (auto& pNewOption : m_pMarketRef->GetOptions())
            {

                //CProduct* pNewProduct = c_mapOption_Product.at(pNewOption);
                CProduct* pNewProduct = pNewOption->GetProduct();
                double nNewProductStep = dBudgetStepLength / m_pPricesRef->GetPriceOfProduct(pNewProduct);

                std::map<COption*, double> mapTryingCombinationAddingProduct = mapCombination;
                if (mapTryingCombinationAddingProduct.end() == mapTryingCombinationAddingProduct.find(pNewOption))
                {
                    mapTryingCombinationAddingProduct[pNewOption] = 0.0;
                }

                mapTryingCombinationAddingProduct[pNewOption] += nNewProductStep;
                double dCurrentLeftMoney = dLeftMoney - dBudgetStepLength;
                
                if (dCurrentLeftMoney < 0.0)
                {
                    //for (auto& nOldOption : c_setOptions)
                    for (auto& pOldOption : m_pMarketRef->GetOptions())
                    {
                        if (pNewOption != pOldOption)
                        {
                            //CProduct* pOldProduct = c_mapOption_Product.at(pOldOption);
                            CProduct* pOldProduct = pOldOption->GetProduct();
                            double dOldProductStep = dBudgetStepLength / m_pPricesRef->GetPriceOfProduct(pOldProduct);
                            if (mapCombination[pOldOption]>=dOldProductStep)
                            {
                                std::map<COption*, double> mapTryingCombinationSwappingProducts = mapTryingCombinationAddingProduct;
                                if (mapTryingCombinationSwappingProducts.end() == mapTryingCombinationSwappingProducts.find(pOldOption))
                                {
                                    mapTryingCombinationSwappingProducts[pOldOption] = 0.0;
                                }

                                mapTryingCombinationSwappingProducts[pOldOption] -= dOldProductStep;
                                dCurrentLeftMoney = dLeftMoney;

                                double dSatisfactionOfTryingCombination = m_upSatisfactionCalculator->CalculateSatisfOfCombidict(mapTryingCombinationSwappingProducts);
                                double dIncrementOfSatisfaction = dSatisfactionOfTryingCombination - dBestPreviousSatisfaction;
 
                                if (dIncrementOfSatisfaction > 0.0)
                                {
                                    mapCombination = mapTryingCombinationSwappingProducts;
                                    bChangeMade = true;
                                    dLeftMoney = dCurrentLeftMoney;
                                    dBestPreviousSatisfaction = dSatisfactionOfTryingCombination;

                                    if (c_traces) std::cout << "Product swapped. dLeftMoney: " << dLeftMoney << std::endl;
                                    if (c_traces) std::cout << "Best previous Satisfaction: " << dBestPreviousSatisfaction << std::endl;
                                    if (c_traces) CUtils::PrintOptions(mapCombination);
                                    break;
                                }



                            }
                        }
                    }
                }
                else
                {
                    double dSatisfactionOfTryingCombination = m_upSatisfactionCalculator->CalculateSatisfOfCombidict(mapTryingCombinationAddingProduct);
                    double dIncrementOfSatisfaction = dSatisfactionOfTryingCombination - dBestPreviousSatisfaction;

                    if (dIncrementOfSatisfaction > 0.0)
                    {
                        mapCombination = mapTryingCombinationAddingProduct;
                        bChangeMade = true;
                        dLeftMoney = dCurrentLeftMoney;
                        dBestPreviousSatisfaction = dSatisfactionOfTryingCombination;

                        if (c_traces) std::cout << "Product added. dLeftMoney: " << dLeftMoney << std::endl;
                        if (c_traces) std::cout << "Best previous Satisfaction: " << dBestPreviousSatisfaction << std::endl;
                        if (c_traces) CUtils::PrintOptions(mapCombination);
                    }
                }
            }

            if (false == bChangeMade)
            {
                if (c_traces) std::cout << "No option found. Exiting" << std::endl;
                break;
            }
        }
    }

    return mapCombination;
}

std::map<pca::COption*, double> pca::CTradeCalculator::AdjustBestCombidictChangingStep(double dBudgetArg, std::map<COption*, double> mapCurrentCombidictArg, double dInitBudgetStepArg, double dTargetBudgetStepArg, int nMaxStepArg)
{
    //var max_step_param : int = max_step_arg
    double dCurrentBudgetStep = dInitBudgetStepArg;
    std::map<COption*, double> mapCurrentBestCombidict = mapCurrentCombidictArg;
    while (dCurrentBudgetStep > dTargetBudgetStepArg)
    {
        mapCurrentBestCombidict = AdjustBestCombidict(dBudgetArg, mapCurrentBestCombidict, dCurrentBudgetStep, nMaxStepArg);
        dCurrentBudgetStep = dCurrentBudgetStep / 2.0;
    }

    return mapCurrentBestCombidict;
}

std::map<pca::COption*, double> pca::CTradeCalculator::ImproveCombination(std::map<CProduct*, double> mapOwnedCombidictArg, std::map<COption*, double> mapCurrentBestCombidictArg, double dInitBudgetStep, double dTargetBudgetStep, int nMaxNumSteps)
{
    double dBudget = m_pPricesRef->CalculateCombidictPrice(mapOwnedCombidictArg);
    //double dInitBudgetStep = dBudget * 8.0;
    
    std::map<pca::COption*, double> mapBestCombidict = AdjustBestCombidictChangingStep(dBudget, mapCurrentBestCombidictArg, dInitBudgetStep, dTargetBudgetStep, nMaxNumSteps);

    return mapBestCombidict;
}

pca::CSatisfactionCalculator* pca::CTradeCalculator::GetSatisfactionCalculatorRef()
{
    return m_upSatisfactionCalculator.get();
}


//func improve_combination(trade_calc_arg:TradeCalculator, owned_combidict_arg : Dictionary, current_best_combidict_arg : Dictionary, budget_step : float, max_num_steps : int)->Dictionary:
//
//  var budget : float = Prices.calculate_combidict_price(owned_combidict_arg)
//  var init_budget_step = budget_step * 8
//  var best_combidict : Dictionary = trade_calc_arg.adjust_best_combidict_changing_step(budget, current_best_combidict_arg, init_budget_step, budget_step, max_num_steps)
//  #			El cálculo tendría que hacerse con pasos de precisión de decimales, y el metodo interpolaría para resultados intermedios
//  return best_combidict




//func adjust_best_combidict_changing_step(budget_arg:float, current_combidict_arg : Dictionary, init_budget_step_arg : float, target_budget_step_arg : float, max_step_arg : int) :
//    var max_step_param : int = max_step_arg
//    var current_budget_step : float = init_budget_step_arg
//    var current_best_combidict : Dictionary = current_combidict_arg
//    while current_budget_step > target_budget_step_arg:
//        current_best_combidict = adjust_best_combidict(budget_arg, current_best_combidict, current_budget_step, max_step_param)
//        current_budget_step = current_budget_step / 2.0
//
//    return current_best_combidict



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

























