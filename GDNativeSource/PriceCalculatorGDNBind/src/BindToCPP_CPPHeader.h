#pragma once

#include <string>
#include <set>
#include <map>

struct strScenarioInfo;

void add_person_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sPerson);
void add_product_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct);
void add_consumption_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption);
void add_saving_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption);
void add_owned_thing_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sProduct, double dAmount);
void add_price_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct, double dPrice);

void add_traded_thing_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sProduct, double dAmount);
void add_consumed_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sOption, double dAmount);
void add_saved_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sOption, double dAmount);



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
//Nuevos:
std::map<std::string, strPreferencesCpp> g_mapPerson_Preferences;




