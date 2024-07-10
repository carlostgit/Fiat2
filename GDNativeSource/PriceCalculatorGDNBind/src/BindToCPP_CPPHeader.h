#pragma once

//"BindToCPP_CPPHeader.h" es una cabecera con métodos y variables C++, del fichero "BindToCPP.cpp"
//El fichero "BindToCPP.cpp" tiene métodos y variables definidos en C++ que sirven para 2 cosas:
//-Hacer las llamadas a métodos PriceCalculator en C++
//-Guardar las variables del escenario que se van a cargar en PriceCalculator, para minimizar la cantidad de código en C que escribir
//-Guardar los resultados de PriceCalculator en una estructura compatible con C, para poder devolver los resultados a Godot a través del GDN
//Además, el fichero "BindToCPP.cpp" tiene también otra cabecera, "BindToCPP.h", con las funciones y estructuras en código C,
//para que puedan ser usados desde el código GND, que está en en C.

#include <string>
#include <set>
#include <map>


#include "AdjustPrices.h"

CAdjustPrices oAdjustPrices;



