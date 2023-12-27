#pragma once

#include <gdnative_api_struct.gen.h>
#include <string.h>

#define MAXSTRING 256

//Punteros a las api, que hay que inicializar en PriceCalculatorGDNBind.c
extern godot_gdnative_core_api_struct* api_for_auxfuncs;// = NULL;
extern godot_gdnative_ext_nativescript_api_struct* nativescript_api_for_auxfuncs;// = NULL;


void PrintInGodotConsole_Text_Size(wchar_t wchar_to_print[], size_t size);
void PrintInGodotConsole_Text(wchar_t wchar_to_print[]);
void PrintInGodotConsole_Int(int intNumber);
void PrintInGodotConsole_Double(double doubleNumber);

//Fin de métodos para imprimir cosas en la consola de GODOT
//////////////////////////////////////////////////////////////

