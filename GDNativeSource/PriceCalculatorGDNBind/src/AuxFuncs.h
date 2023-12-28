#pragma once
#include "PriceCalculatorGDNBind.h"
#include <gdnative_api_struct.gen.h>
#include <string.h>


void PrintInGodotConsole_Text_Size(wchar_t wchar_to_print[], size_t size);
void PrintInGodotConsole_Text(wchar_t wchar_to_print[]);
void PrintInGodotConsole_Int(int intNumber);
void PrintInGodotConsole_Double(double doubleNumber);

//Fin de métodos para imprimir cosas en la consola de GODOT
//////////////////////////////////////////////////////////////

