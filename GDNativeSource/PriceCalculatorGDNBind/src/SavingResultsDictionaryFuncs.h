#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"


void SaveProductPriceResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg);
void SaveProductAmountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SaveTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SavePersonProdamountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg);
void SavePersonTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg);
void SaveScenarioInfoResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);
