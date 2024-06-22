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
struct strScenarioInfo;

//Funciones auxiliares usados por LoadPriceCalculationResultsFromPriceCalculatorToScenarioInfoStruct
//para meter los resultados de los c�lculos desde PriceCalculator a la estructura strScenarioInfo
static void add_person_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sPerson);
static void add_product_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct);
static void add_consumption_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption);
static void add_saving_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption);
static void add_owned_thing_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sProduct, double dAmount);
static void add_price_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct, double dPrice);

static void add_traded_thing_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sProduct, double dAmount);
static void add_consumed_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sOption, double dAmount);
static void add_saved_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sOption, double dAmount);

//Metodo para meter los resultados de los calculos desde CPriceCalculator a strScenarioInfo
void LoadPriceCalculationResultsFromPriceCalculatorToScenarioInfoStruct(pca::CPriceCalculator* pPriceCalculator, struct strScenarioInfo* pstrScenarioInfoOutput);

//M�todo para cargar las variables globales en CPriceCalculator y ajustar precios
void LoadGlobalVariablesIntoPriceCalculatorAndAdjustPrices(pca::CPriceCalculator* pPriceCalculator);

//Variables globales donde se guardan los datos del escenario que se tiene que calcular
//Datos del escenario que se va a calcular
std::set<std::string> g_setPersons;
std::set<std::string> g_setProducts;
std::set<std::string> g_setConsumptionOptions;
std::set<std::string> g_setSavingOptions;
std::map<std::string, std::map<std::string, double> > g_mapPerson_ProdAmount;
std::map<std::string, std::string> g_mapOptionProduct;
std::string g_sCurrency;
struct strPreferencesCpp
{
	std::map<std::string, double> mapOptionMaxSatisf;
	std::map<std::string, double> mapOptionPrefAt0;
};
std::map<std::string, strPreferencesCpp> g_mapPerson_Preferences;




