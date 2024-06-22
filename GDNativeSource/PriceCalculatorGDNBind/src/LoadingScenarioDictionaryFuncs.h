#pragma once
#include <gdnative_api_struct.gen.h>
#include <string.h>


//#pragma warning(error: 4013) //Para que en el código, sea un error usar una función sin declaración
//Lo comento, porque al final he hecho lo mismo configurando las propiedades del proyecto
//añadiendo 4013 en "Disable Specific Warnings"
//warning C4013 typically indicates that a function declaration is not found.



//Métodos para procesar la información del escenario que viene en un diccionario desde GODOT

void LoadScenarioInfoFromGDNIntoGlobalCPPVariables(godot_dictionary* pgodict_scenario_info_arg, const godot_gdnative_core_api_struct* api_arg);
