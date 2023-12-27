#include "SavingResultsDictionaryFuncs.h"
#include "AuxFuncs.h"




void SaveProductPriceResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg)
{
    //Pruebo a salvar datos de los precios primero
    int i = 0;
    for (i = 0;i < pstr_scenario_info->prices.n_num_prices;i++)
    {
        double dPrice = pstr_scenario_info->prices.prod_price[i].dAmount;

        wchar_t* pwchar_product_name = pstr_scenario_info->prices.prod_price[i].name_product.wc_name;
        int size = wcslen(pwchar_product_name);
        godot_string godstring_product_name;
        api_arg->godot_string_new_with_wide_string(&godstring_product_name, pwchar_product_name, size);
        godot_variant godvar_product_name;
        api_arg->godot_variant_new_string(&godvar_product_name, &godstring_product_name);

        godot_real godreal_price = dPrice;
        godot_variant godvar_product_price;
        api_arg->godot_variant_new_real(&godvar_product_price, dPrice);

        api_arg->godot_dictionary_set(pgodict_product_price, &godvar_product_name, &godvar_product_price);
    }
}

void SaveProductAmountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->owned_things.person_prod_amounts[person_index].n_num_prod_amounts;i++)
    {
        wchar_t* pwchar_product_name = pstr_scenario_info->owned_things.person_prod_amounts[person_index].prod_amounts[i].name_product.wc_name;
        int size = wcslen(pwchar_product_name);
        godot_string godstring_product_name;
        api_arg->godot_string_new_with_wide_string(&godstring_product_name, pwchar_product_name, size);
        godot_variant godvar_product_name;
        api_arg->godot_variant_new_string(&godvar_product_name, &godstring_product_name);

        const double dAmount = pstr_scenario_info->owned_things.person_prod_amounts[person_index].prod_amounts[i].dAmount;
        godot_variant godvar_amount;
        api_arg->godot_variant_new_real(&godvar_amount, dAmount);

        api_arg->godot_dictionary_set(pgodict_product_amount, &godvar_product_name, &godvar_amount);
    }

}

void SaveTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->traded_things.person_prod_amounts[person_index].n_num_prod_amounts;i++)
    {
        wchar_t* pwchar_product_name = pstr_scenario_info->traded_things.person_prod_amounts[person_index].prod_amounts[i].name_product.wc_name;
        int size = wcslen(pwchar_product_name);
        godot_string godstring_product_name;
        api_arg->godot_string_new_with_wide_string(&godstring_product_name, pwchar_product_name, size);
        godot_variant godvar_product_name;
        api_arg->godot_variant_new_string(&godvar_product_name, &godstring_product_name);

        const double dAmount = pstr_scenario_info->traded_things.person_prod_amounts[person_index].prod_amounts[i].dAmount;
        godot_variant godvar_amount;
        api_arg->godot_variant_new_real(&godvar_amount, dAmount);

        api_arg->godot_dictionary_set(pgodict_product_amount, &godvar_product_name, &godvar_amount);
    }
}


void SavePersonProdamountResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->owned_things.n_num_persons;i++)
    {
        wchar_t* pwchar_person_name = pstr_scenario_info->owned_things.person_prod_amounts[i].name_person.wc_name;
        int size = wcslen(pwchar_person_name);
        godot_string godstring_person_name;
        api_arg->godot_string_new_with_wide_string(&godstring_person_name, pwchar_person_name, size);
        godot_variant godvar_person_name;
        api_arg->godot_variant_new_string(&godvar_person_name, &godstring_person_name);

        godot_dictionary godict_product_amount;
        api_arg->godot_dictionary_new(&godict_product_amount);
        SaveProductAmountResults(pstr_scenario_info, &godict_product_amount, i, api_arg);

        godot_variant godvar_product_amount;
        api_arg->godot_variant_new_dictionary(&godvar_product_amount, &godict_product_amount);

        api_arg->godot_dictionary_set(pgodict_person_prodamount, &godvar_person_name, &godvar_product_amount);
    }
}

void SavePersonTradedResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->traded_things.n_num_persons;i++)
    {
        wchar_t* pwchar_person_name = pstr_scenario_info->traded_things.person_prod_amounts[i].name_person.wc_name;
        int size = wcslen(pwchar_person_name);
        godot_string godstring_person_name;
        api_arg->godot_string_new_with_wide_string(&godstring_person_name, pwchar_person_name, size);
        godot_variant godvar_person_name;
        api_arg->godot_variant_new_string(&godvar_person_name, &godstring_person_name);

        godot_dictionary godict_product_amount;
        api_arg->godot_dictionary_new(&godict_product_amount);
        SaveTradedResults(pstr_scenario_info, &godict_product_amount, i, api_arg);

        godot_variant godvar_product_amount;
        api_arg->godot_variant_new_dictionary(&godvar_product_amount, &godict_product_amount);

        api_arg->godot_dictionary_set(pgodict_person_traded, &godvar_person_name, &godvar_product_amount);
    }
}


void SaveScenarioInfoResults(struct strScenarioInfo* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg)
{
    //var text_dict_arg : Dictionary = {
//    "Prices":
//                {"nut":1.1,"chocolate" : 2.3,"candy" : 3.5},
//    "Owned" : {
//        "Peter":
//                {"nut":1,"chocolate" : 2,"candy" : 3},
//        "George" :
//                {"nut":4,"chocolate" : 5,"candy" : 6}
//         },
//    "Traded" : {
//        "Peter":
//                {"nut":1,"chocolate" : -2.1,"candy" : 3.4},
//        "George" :
//                {"nut":-1.4,"chocolate" : 5.3,"candy" : -6.1}
//         },
//     "Consumed" : {
//        "Peter":
//                {"nut_consumtion":1,"chocolate_consumption" : -2.1,"candy_consumption" : 3.4},
//        "George" :
//                {"nut_consumption":-1.4,"chocolate_consumption" : 5.3,"candy_consumption" : -6.1}
//         },
//     "Saved" : {
//        "Peter":
//                {"nut_saving":1,"chocolate_saving" : -2.1,"candy_saving" : 3.4},
//        "George" :
//                {"nut_saving":-1.4,"chocolate_saving" : 5.3,"candy_saving" : -6.1}
//         },
// 
//}

    godot_dictionary godict_scenario_info = (*pgdict_results_scenario_info);

    //////////////
    //Save Prices:
    godot_dictionary godict_product_price;
    api_arg->godot_dictionary_new(&godict_product_price);

    SaveProductPriceResults(pstr_scenario_info, &godict_product_price, api_arg);

    wchar_t* pwchar_prices = L"Prices";
    int size_prices = wcslen(pwchar_prices);
    godot_string godstring_prices;
    api_arg->godot_string_new_with_wide_string(&godstring_prices, pwchar_prices, size_prices);
    godot_variant godvar_prices;
    api_arg->godot_variant_new_string(&godvar_prices, &godstring_prices);

    godot_variant godvar_product_price;
    api_arg->godot_variant_new_dictionary(&godvar_product_price, &godict_product_price);

    //Se añade el diccionario de precios al diccionario del escenario
    api_arg->godot_dictionary_set(&godict_scenario_info, &godvar_prices, &godvar_product_price);

    /////////////
    //Save Owned:
    godot_dictionary godict_person_prodamount;
    api_arg->godot_dictionary_new(&godict_person_prodamount);

    SavePersonProdamountResults(pstr_scenario_info, &godict_person_prodamount, api_arg);

    wchar_t* pwchar_owned = L"Owned";
    int size_owned = wcslen(pwchar_owned);
    godot_string godstring_owned;
    api_arg->godot_string_new_with_wide_string(&godstring_owned, pwchar_owned, size_owned);
    godot_variant godvar_owned;
    api_arg->godot_variant_new_string(&godvar_owned, &godstring_owned);

    godot_variant godvar_person_prodamount;
    api_arg->godot_variant_new_dictionary(&godvar_person_prodamount, &godict_person_prodamount);

    //Se añade el diccionario de owned al diccionario del escenario
    api_arg->godot_dictionary_set(&godict_scenario_info, &godvar_owned, &godvar_person_prodamount);

    //////////////
    //Save Traded:
    godot_dictionary godict_person_traded;
    api_arg->godot_dictionary_new(&godict_person_traded);

    SavePersonTradedResults(pstr_scenario_info, &godict_person_traded, api_arg);

    wchar_t* pwchar_traded = L"Traded";
    int size_traded = wcslen(pwchar_traded);
    godot_string godstring_traded;
    api_arg->godot_string_new_with_wide_string(&godstring_traded, pwchar_traded, size_traded);
    godot_variant godvar_traded;
    api_arg->godot_variant_new_string(&godvar_traded, &godstring_traded);

    godot_variant godvar_person_traded;
    api_arg->godot_variant_new_dictionary(&godvar_person_traded, &godict_person_traded);

    //Se añade el diccionario de traded al diccionario del escenario
    api_arg->godot_dictionary_set(&godict_scenario_info, &godvar_traded, &godvar_person_traded);

    //TODO
}
