#pragma once
#include "PriceCalculatorGDNBind.h"
#include <gdnative_api_struct.gen.h>
#include <string.h>

//Métodos auxiliares en C, para usar en GDN

//////////////////////////////////////////////////////////////
//Inicio de métodos para imprimir cosas en la consola de GODOT

void print_in_godot_console_Text_Size(wchar_t wchar_to_print[], size_t size);
void print_in_godot_console_Text(wchar_t wchar_to_print[]);
void print_in_godot_console_Int(int intNumber);
void print_in_godot_console_Double(double doubleNumber);

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

godot_variant get_govar_from_AFName(const struct strAFName* pName, const godot_gdnative_core_api_struct* api_arg);
struct strAFName get_AFName_from_govar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg);
struct strAFNames get_AFNames_from_govar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg);

struct strAFDictKeys get_AFDictKeys_from_godict(godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
struct strAFName get_AFName_from_godict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
double get_number_from_godict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);

struct strAFNames get_AFNames_from_godict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);
godot_dictionary get_godict_from_godict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg);

//Fin de los métodos para leer diccionarios de godot
///////////////////////////////////////////////////////

///////////////////////////////////////////////////////
//Inicio de los métodos para copiar wchar_t
struct strAFName get_AFName_from_wchar(wchar_t wc_name[256]);
//
///////////////////////////////////////////////////////