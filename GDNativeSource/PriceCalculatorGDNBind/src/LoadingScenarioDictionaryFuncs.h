#pragma once
#include <gdnative_api_struct.gen.h>
#include <string.h>


//#pragma warning(error: 4013) //Para que en el c�digo, sea un error usar una funci�n sin declaraci�n
//Lo comento, porque al final he hecho lo mismo configurando las propiedades del proyecto
//a�adiendo 4013 en "Disable Specific Warnings"
//warning C4013 typically indicates that a function declaration is not found.

//M�todos para procesar la informaci�n del escenario que viene en un diccionario desde GODOT

//C�lculo de mejor combinaci�n de opciones para un presupuest:
void load_data_from_godot_into_adjust_best_combidict_input_object(godot_dictionary* godict_input_arg, const godot_gdnative_core_api_struct* api_arg);

//C�lculo de precio:
void load_data_from_godot_into_adjust_prices_input_object(godot_dictionary* pgodict_scenario_info_arg, const godot_gdnative_core_api_struct* api_arg);
