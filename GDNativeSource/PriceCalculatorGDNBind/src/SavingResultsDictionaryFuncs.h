#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"


//Private:
void GetProductPriceGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg);
void GetProductAmountGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetTradedAmountGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetConsumedAmountGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_consumed_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetSavedAmountGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_saved_amount, int person_index, const godot_gdnative_core_api_struct* api_arg);
void GetPersonProdamountGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg);
void GetPersonTradedGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg);
void GetPersonConsumedGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_consumed, const godot_gdnative_core_api_struct* api_arg);
void GetPersonSavedGodictFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_saved, const godot_gdnative_core_api_struct* api_arg);

//Public:
void GetGodotDictionaryFromScenarioInfoStruct(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg);
