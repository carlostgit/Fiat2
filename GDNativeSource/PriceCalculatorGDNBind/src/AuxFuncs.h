#pragma once
#include "PriceCalculatorGDNBind.h"
#include <gdnative_api_struct.gen.h>
#include <string.h>


//////////////////////////////////////////////////////////////
//Inicio de métodos para imprimir cosas en la consola de GODOT

void PrintInGodotConsole_Text_Size(wchar_t wchar_to_print[], size_t size);
void PrintInGodotConsole_Text(wchar_t wchar_to_print[]);
void PrintInGodotConsole_Int(int intNumber);
void PrintInGodotConsole_Double(double doubleNumber);

//Fin de métodos para imprimir cosas en la consola de GODOT
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////
//Inicio de los métodos para leer diccionarios de godot

struct strAFName
{
	wchar_t wc_name[256];
};

struct strAFDictKeys
{
	int n_num_of_keys;
	struct strAFName keys[25];
};

struct strAFNames
{
	int n_num_of_values;
	struct strAFName names[25];
};

struct strAFNumbers
{
	int n_num_of_values;
	double numbers[25];
};

godot_variant GetGovarFromAFName(const struct strAFName* pName, const godot_gdnative_core_api_struct* api_arg);
struct strAFName GetAFNameFromGovar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg);
struct strAFNames GetAFNamesFromGovar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg);

struct strAFDictKeys GetKeysFromGodict(godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
struct strAFName GetNameFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
struct strAFNames GetNamesFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
godot_dictionary GetGodictFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);


//Fin de los métodos para leer diccionarios de godot
///////////////////////////////////////////////////////

