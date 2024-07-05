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

namespace pca {
	class CPriceCalculator;
}
struct strAdjustPriceResults; //Todo: Cambiar nombre a algo as� como strAdjustPriceResults

//Todo: Crear resultados de 
//struct strAdjustPriceResults;

//Funciones auxiliares usados por LoadAdjustPriceResultsFromPriceCalculatorToStruct
//para meter los resultados de los c�lculos desde PriceCalculator a la estructura strAdjustPriceResults
//static void add_person_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sPerson);
//static void add_product_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct);
//static void add_consumption_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
//static void add_saving_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
//static void add_owned_thing_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
//static void add_price_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct, double dPrice);
//
//static void add_traded_thing_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
//static void add_consumed_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
//static void add_saved_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);

//Metodo para meter los resultados de los calculos desde CPriceCalculator a strAdjustPriceResults
void LoadAdjustPriceResultsFromPriceCalculatorToStruct(pca::CPriceCalculator* pPriceCalculator, struct strAdjustPriceResults* pstrAdjustPriceResultsOutput);

//M�todo para cargar las variables globales en CPriceCalculator y ajustar precios
void LoadInputDataIntoPriceCalculatorAndAdjustPrices(pca::CPriceCalculator* pPriceCalculator);

//Variables globales donde se guardan los datos del escenario que se va a calcular:
//////////////////// (Igual esto se puede llevar a estructuras o clases)
//C�lculo de precios:
//Variables globales donde se guardan los datos del escenario que se tiene que calcular
//Datos del escenario que se va a calcular
//Todo: Meter estas variables dentro de una clase que sea algo as� como: class CAjustPricesInput
//std::set<std::string> g_setPersons;
//std::set<std::string> g_setProducts;
//std::set<std::string> g_setConsumptionOptions;
//std::set<std::string> g_setSavingOptions;
//std::map<std::string, std::map<std::string, double> > g_mapPerson_ProdAmount;
//std::map<std::string, std::string> g_mapOptionProduct;
//std::string g_sCurrency;
//struct strPreferencesCpp
//{
//	std::map<std::string, double> mapOptionMaxSatisf;
//	std::map<std::string, double> mapOptionPrefAt0;
//};
//std::map<std::string, strPreferencesCpp> g_mapPerson_Preferences;

//////////////////////
//TODO: C�lculo de opciones escogidas para un presupuesto
//Variables globales para calcular las opciones escogidas por un TradeCalculator para un presupuesto
//Todo: Meter estas variables dentro de una clase que sea algo as� como: class CalculateOptionsForBudgetInput
//strPreferencesCpp g_strPreferences;
//std::set<std::string> g_setProducts;
//std::set<std::string> g_setConsumptionOptions;
//double g_dBudget;

//Para calcular las opciones en un rango de presupuestos, habr�a que tener lo mismo, y adem�s un g_dCalcStep
//Todo: Meter estas variables dentro de una clase que sea algo as� como: class CalculateOptionsForRangeOfBudgetInput
//Esto �ltimo se tiene que hacer con un l�mite, porque el n�mero de datos que se pueden devolver de una sola vez es limitado

#include "AdjustPrices.h"

CAdjustPrices oAdjustPrices;



