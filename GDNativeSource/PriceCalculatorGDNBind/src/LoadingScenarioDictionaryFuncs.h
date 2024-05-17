#pragma once
#include <gdnative_api_struct.gen.h>
#include <string.h>


//#pragma warning(error: 4013) //Para que en el código, sea un error usar una función sin declaración
//Lo comento, porque al final he hecho lo mismo configurando las propiedades del proyecto
//añadiendo 4013 en "Disable Specific Warnings"
//warning C4013 typically indicates that a function declaration is not found.



//Métodos para procesar la información del escenario que viene en un diccionario desde GODOT

//TODO ProcessScenarioPersonOptionPreferences
//void ProcessScenarioPerson_Typeofpref_OptionPreferences(godot_string* pgostring_person_arg, godot_dictionary* pgodict_typeofpref_optionpreferences, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioPreferences(godot_dictionary* pgodict_preferences_arg, const godot_gdnative_core_api_struct* api_arg);

//void ProcessScenarioPersons(godot_array* pgodarray_persons_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioProducts(godot_array* pgodarray_products_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioConsumption(godot_array* pgodarray_consumption_options_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioSaving(godot_array* pgodarray_saving_options_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioPersonOwned(godot_string* pgostring_person_arg, godot_dictionary* pgodict_product_amount_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioOwned(godot_dictionary* pgodict_owned_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioOptionProduct(godot_dictionary* pgodict_option_product_arg, const godot_gdnative_core_api_struct* api_arg);
//void ProcessScenarioCurrency(godot_string* pgostring_currency_arg, const godot_gdnative_core_api_struct* api_arg);

void ProcessScenarioInfo(godot_dictionary* pgodict_scenario_info_arg, const godot_gdnative_core_api_struct* api_arg);
