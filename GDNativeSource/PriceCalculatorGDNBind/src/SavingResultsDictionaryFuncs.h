#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"

//Métodos para cargar en una estructura godot_dictionary la información de la estructura strAdjustPriceResults
// que contiene los resultados de los cálculos hechos en PriceCalculator

//Métodos para Adjust Prices:

//Private:
void get_product_price_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg);
void get_product_amount_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void get_traded_amount_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void get_consumed_amount_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_consumed_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void get_saved_amount_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_saved_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void get_person_prodamount_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg);
void get_person_traded_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg);
void get_person_consumed_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_consumed, const godot_gdnative_core_api_struct* api_arg);
void get_person_saved_godict_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_saved, const godot_gdnative_core_api_struct* api_arg);

//Public:
void get_godot_dictionary_from_adjust_price_results(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);


//Métodos para Adjust Best Combination:

//Public:
void get_godot_dictionary_from_adjust_best_combination(struct strAdjustBestCombinationResults* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);