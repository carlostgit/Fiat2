#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"


void SaveProductPriceResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg);
void SaveProductAmountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SaveTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SaveConsumedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_consumed_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SaveSavedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_saved_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void SavePersonProdamountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg);
void SavePersonTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg);
void SavePersonConsumedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_consumed, const godot_gdnative_core_api_struct* api_arg);
void SavePersonSavedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_saved, const godot_gdnative_core_api_struct* api_arg);
void SaveScenarioInfoResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);
