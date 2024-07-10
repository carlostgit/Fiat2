#pragma once

//"BindToCPP_CPPHeader.h" es una cabecera con m�todos y variables C++, del fichero "BindToCPP.cpp"
//El fichero "BindToCPP.cpp" tiene m�todos y variables definidos en C++ que sirven para 2 cosas:
//-Hacer las llamadas a m�todos PriceCalculator en C++
//-Guardar las variables del escenario que se van a cargar en PriceCalculator, para minimizar la cantidad de c�digo en C que escribir
//-Guardar los resultados de PriceCalculator en una estructura compatible con C, para poder devolver los resultados a Godot a trav�s del GDN
//Adem�s, el fichero "BindToCPP.cpp" tiene tambi�n otra cabecera, "BindToCPP.h", con las funciones y estructuras en c�digo C,
//para que puedan ser usados desde el c�digo GND, que est� en en C.

#include <string>
#include <set>
#include <map>


#include "AdjustPrices.h"

CAdjustPrices oAdjustPrices;



