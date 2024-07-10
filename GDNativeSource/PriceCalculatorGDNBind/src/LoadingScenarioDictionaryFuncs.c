#include "LoadingScenarioDictionaryFuncs.h"
#include "BindToCPP.h"
#include "AuxFuncs.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////
//Inicio de métodos para procesar la información que llega desde GODOT

//Método para procesar la información del escenario que viene en un diccionario desde GODOT
void load_data_from_godot_into_adjust_prices_input_object(godot_dictionary* pgodict_scenario_info_arg, const godot_gdnative_core_api_struct* api_arg)
{
    //Primero Reseteamos la información
    //ResetAdjustPricesDataInput();
    reset_adjust_prices_data_input();

    //var text_dict_arg : Dictionary = {
    //    "Persons": ["Peter","George"] ,
    //    "Products" : ["nut","chocolate","candy"] ,
    //    "Consumption" : ["nut_consumption","chocolate_consumption","candy_consumption"] ,
    //    "Owned" : {
    //        "Peter":
    //                {"nut":1,"chocolate" : 2,"candy" : 3},
    //        "George" :
    //                {"nut":4,"chocolate" : 5,"candy" : 6}
    //    },
    //    "OptionProduct":{"nut_consumption":"nut","chocolate_consumption" : "chocolate","candy_consumption" : "candy"},
    // #  "Preferences": {
//#				"Peter":					
//#						{
//#							"PreferenceAt0":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#							"MaximumSatisfaction":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#						},
//#				"George":					
//#						{
//#							"PreferenceAt0":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#							"MaximumSatisfaction":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#						},
//#				},

    //    "Currency" : "nut"
    //}

    //Código nuevo de carga
    {
        godot_dictionary godict_scenario_info = (*pgodict_scenario_info_arg);
        struct strAFDictKeys strKeys = get_keys_from_godict(&godict_scenario_info, api_arg);

        //////////
        //Owned
        //    "Owned" : {
        //        "Peter":
        //                {"nut":1,"chocolate" : 2,"candy" : 3},
        //        "George" :
        //                {"nut":4,"chocolate" : 5,"candy" : 6}
        //    },
        {
            wchar_t wchar_owned[256] = L"Owned";
            struct strAFName strOwned = get_Name_from_wchar(wchar_owned);
            godot_dictionary dict_owned = get_godict_from_godict(&strOwned, &godict_scenario_info, api_arg);
            struct strAFDictKeys strPersons = get_keys_from_godict(&dict_owned, api_arg);

            for (int iPers = 0;iPers < strPersons.n_num_of_keys;iPers++)
            {
                struct strAFName strPerson = strPersons.keys[iPers];
                godot_dictionary godict_ownedbyperson = get_godict_from_godict(&strPerson, &dict_owned, api_arg);
                struct strAFDictKeys strProducts = get_keys_from_godict(&godict_ownedbyperson, api_arg);

                for (int iProd = 0;iProd < strProducts.n_num_of_keys;iProd++)
                {
                    struct strAFName strProduct = strProducts.keys[iProd];
                    struct strAFName strAmount = get_Name_from_godict(&strProduct, &godict_ownedbyperson, api_arg);
                    double dAmount = get_number_from_godict(&strProduct, &godict_ownedbyperson, api_arg);
                    add_person_owned(strPerson.wc_name, 256, strProduct.wc_name, 256, dAmount);
                }
            }
        }

        /////////
        //Persons
        //    "Persons": ["Peter","George"] ,
        {
            wchar_t wchar_persons[256] = L"Persons";
            struct strAFName strPersons2 = get_Name_from_wchar(wchar_persons);
            struct strAFNames strNames = get_Names_from_godict(&strPersons2, &godict_scenario_info, api_arg);
            int num_persons = strNames.n_num_of_values;

            for (int iPers = 0;iPers < num_persons;iPers++)
            {
                struct strAFName strPerson = strNames.names[iPers];
                add_person(strPerson.wc_name, 256);
            }
        }
        /////////
        //Products
        //    "Products" : ["nut","chocolate","candy"] ,
        {
            wchar_t wchar_products[256] = L"Products";
            struct strAFName strProducts2 = get_Name_from_wchar(wchar_products);
            struct strAFNames strNames = get_Names_from_godict(&strProducts2, &godict_scenario_info, api_arg);
            int num_products = strNames.n_num_of_values;

            for (int iProds = 0;iProds < num_products;iProds++)
            {
                struct strAFName strProduct = strNames.names[iProds];
                add_product(strProduct.wc_name, 256);
            }
        }

        //Consumption
        //"Consumption" : ["nut_consumption", "chocolate_consumption", "candy_consumption"] ,
        {
            wchar_t wchar_consumption[256] = L"Consumption";
            struct strAFName strConsumption2 = get_Name_from_wchar(wchar_consumption);
            struct strAFNames strNames = get_Names_from_godict(&strConsumption2, &godict_scenario_info, api_arg);
            int num_consumption = strNames.n_num_of_values;

            for (int iConsumption = 0;iConsumption < num_consumption;iConsumption++)
            {
                struct strAFName strConsumption = strNames.names[iConsumption];
                add_consumption_option(strConsumption.wc_name, 256);
            }
        }

        //OptionProduct
        //    "OptionProduct":{"nut_consumption":"nut","chocolate_consumption" : "chocolate","candy_consumption" : "candy"},
        {
            wchar_t wchar_option_product[256] = L"OptionProduct";
            struct strAFName strOptionProduct = get_Name_from_wchar(wchar_option_product);
            godot_dictionary dict_option_product = get_godict_from_godict(&strOptionProduct, &godict_scenario_info, api_arg);
            struct strAFDictKeys strOptions = get_keys_from_godict(&dict_option_product, api_arg);

            for (int iOptions = 0;iOptions < strOptions.n_num_of_keys;iOptions++)
            {
                struct strAFName strOption = strOptions.keys[iOptions];
                struct strAFName strProduct = get_Name_from_godict(&strOption, &dict_option_product, api_arg);
                add_option_product(strOption.wc_name, 256, strProduct.wc_name, 256);
            }
        }
        //

        //Preferences
        // #  "Preferences": {
//#				"Peter":					
//#						{
//#							"PreferenceAt0":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#							"MaximumSatisfaction":
//#									{"bill_consumption":1.0,"chocolate_consumption":1.0,"candy_consumption":1.0},
//#						},
//#	
        {
            wchar_t wchar_preferences[256] = L"Preferences";
            struct strAFName strPreferences = get_Name_from_wchar(wchar_preferences);
            godot_dictionary dict_person_preferences = get_godict_from_godict(&strPreferences, &godict_scenario_info, api_arg);
            struct strAFDictKeys strPersons = get_keys_from_godict(&dict_person_preferences, api_arg);

            for (int iPersons = 0;iPersons < strPersons.n_num_of_keys;iPersons++)
            {
                struct strAFName strPerson = strPersons.keys[iPersons];
                godot_dictionary dict_type_preferences = get_godict_from_godict(&strPerson, &dict_person_preferences, api_arg);

                //debug
                //struct strAFDictKeys strPrefTypes = GetKeysFromGodict(&dict_person_preferences, api_arg);
                //

                {
                    wchar_t wchar_PreferenceAt0[256] = L"PreferenceAt0";

                    struct strAFName strPreferenceAt0 = get_Name_from_wchar(wchar_PreferenceAt0);
                    godot_dictionary dict_option_PreferenceAt0 = get_godict_from_godict(&strPreferenceAt0, &dict_type_preferences, api_arg);
                    struct strAFDictKeys strOptions = get_keys_from_godict(&dict_option_PreferenceAt0, api_arg);

                    wchar_t wchar_MaximumSatisfaction[256] = L"MaximumSatisfaction";
                    godot_dictionary dict_option_MaximumSatisfaction = get_godict_from_godict(&wchar_MaximumSatisfaction, &dict_type_preferences, api_arg);
                    struct strAFDictKeys strOptionsMaxSat = get_keys_from_godict(&dict_option_MaximumSatisfaction, api_arg);

                    if (strOptionsMaxSat.n_num_of_keys != strOptions.n_num_of_keys)
                        printf("strOptionsMaxSat.n_num_of_keys != strOptions.n_num_of_keys \n");

                    for (int iOptions = 0;iOptions < strOptions.n_num_of_keys;iOptions++)
                    {
                        if (strOptionsMaxSat.keys[iOptions].wc_name != strOptions.keys[iOptions].wc_name)
                            printf("strOptionsMaxSat.keys[iOptions]!= strOptions.keys[iOptions] \n");

                        struct strAFName strOption = strOptions.keys[iOptions];
                        //struct strAFName PreferenceAt0 = GetNameFromGodict(&strOption, &dict_option_PreferenceAt0, api_arg);
                        double dPreferenceAt0 = get_number_from_godict(&strOption, &dict_option_PreferenceAt0, api_arg);
                        
                        //struct strAFName MaximumSatisfaction = GetNameFromGodict(&strOption, &dict_option_MaximumSatisfaction, api_arg);
                        double dMaximumSatisfaction = get_number_from_godict(&strOption, &dict_option_MaximumSatisfaction, api_arg);

                        add_preferences_for_person(strPerson.wc_name, strOption.wc_name, dMaximumSatisfaction, dPreferenceAt0);
                        //add_currency(strName.wc_name, 256);
                        //TODO: Falta el método para añadir esto

                    }
                }
            }
        }

        //Currency
        //    "Currency" : "nut"
        {
            wchar_t wchar_currency[256] = L"Currency";
            struct strAFName strCurrency = get_Name_from_wchar(wchar_currency);
            struct strAFName strName = get_Name_from_godict(&strCurrency, &godict_scenario_info, api_arg);
            int num_persons = strName.wc_name;
            add_currency(strName.wc_name, 256);
        }
        //

        //Seguir con el resto:
        //TODO SEGUIR POR AQUI

    }
}

