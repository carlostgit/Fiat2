#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"

//Métodos para cargar en una estructura godot_dictionary la información de la estructura strAdjustPriceResults
// que contiene los resultados de los cálculos hechos en PriceCalculator

//Private:
void GetProductPriceGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg);
void GetProductAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetTradedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetConsumedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_consumed_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetSavedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_saved_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetPersonProdamountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg);
void GetPersonTradedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg);
void GetPersonConsumedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_consumed, const godot_gdnative_core_api_struct* api_arg);
void GetPersonSavedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_saved, const godot_gdnative_core_api_struct* api_arg);

//Public:
void GetGodotDictionaryFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);
