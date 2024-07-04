#include "SavingResultsDictionaryFuncs.h"
#include "AuxFuncs.h"

void GetProductPriceGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_price, const godot_gdnative_core_api_struct* api_arg)
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

void GetProductAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
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

void GetTradedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_product_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
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

void GetConsumedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_consumed_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->consumed_options.person_option_amounts[person_index].n_num_option_amounts;i++)
    {
        wchar_t* pwchar_option_name = pstr_scenario_info->consumed_options.person_option_amounts[person_index].option_amounts[i].name_option.wc_name;
        int size = wcslen(pwchar_option_name);
        godot_string godstring_option_name;
        api_arg->godot_string_new_with_wide_string(&godstring_option_name, pwchar_option_name, size);
        godot_variant godvar_option_name;
        api_arg->godot_variant_new_string(&godvar_option_name, &godstring_option_name);

        const double dAmount = pstr_scenario_info->consumed_options.person_option_amounts[person_index].option_amounts[i].dAmount;
        godot_variant godvar_amount;
        api_arg->godot_variant_new_real(&godvar_amount, dAmount);

        api_arg->godot_dictionary_set(pgodict_consumed_amount, &godvar_option_name, &godvar_amount);
    }
}

void GetSavedAmountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_saved_amount, int person_index, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->saved_options.person_option_amounts[person_index].n_num_option_amounts;i++)
    {
        wchar_t* pwchar_option_name = pstr_scenario_info->saved_options.person_option_amounts[person_index].option_amounts[i].name_option.wc_name;
        int size = wcslen(pwchar_option_name);
        godot_string godstring_option_name;
        api_arg->godot_string_new_with_wide_string(&godstring_option_name, pwchar_option_name, size);
        godot_variant godvar_option_name;
        api_arg->godot_variant_new_string(&godvar_option_name, &godstring_option_name);

        const double dAmount = pstr_scenario_info->saved_options.person_option_amounts[person_index].option_amounts[i].dAmount;
        godot_variant godvar_amount;
        api_arg->godot_variant_new_real(&godvar_amount, dAmount);

        api_arg->godot_dictionary_set(pgodict_saved_amount, &godvar_option_name, &godvar_amount);
    }
}


void GetPersonProdamountGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_prodamount, const godot_gdnative_core_api_struct* api_arg)
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
        GetProductAmountGodictFromAdjustPriceResults(pstr_scenario_info, &godict_product_amount, i, api_arg);

        godot_variant godvar_product_amount;
        api_arg->godot_variant_new_dictionary(&godvar_product_amount, &godict_product_amount);

        api_arg->godot_dictionary_set(pgodict_person_prodamount, &godvar_person_name, &godvar_product_amount);
    }
}

void GetPersonTradedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_traded, const godot_gdnative_core_api_struct* api_arg)
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
        GetTradedAmountGodictFromAdjustPriceResults(pstr_scenario_info, &godict_product_amount, i, api_arg);

        godot_variant godvar_product_amount;
        api_arg->godot_variant_new_dictionary(&godvar_product_amount, &godict_product_amount);

        api_arg->godot_dictionary_set(pgodict_person_traded, &godvar_person_name, &godvar_product_amount);
    }
}

void GetPersonConsumedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_consumed, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->consumed_options.n_num_persons;i++)
    {
        wchar_t* pwchar_person_name = pstr_scenario_info->consumed_options.person_option_amounts[i].name_person.wc_name;
        int size = wcslen(pwchar_person_name);
        godot_string godstring_person_name;
        api_arg->godot_string_new_with_wide_string(&godstring_person_name, pwchar_person_name, size);
        godot_variant godvar_person_name;
        api_arg->godot_variant_new_string(&godvar_person_name, &godstring_person_name);

        godot_dictionary godict_consumed_amount;
        api_arg->godot_dictionary_new(&godict_consumed_amount);
        GetConsumedAmountGodictFromAdjustPriceResults(pstr_scenario_info, &godict_consumed_amount, i, api_arg);

        godot_variant godvar_consumed_amount;
        api_arg->godot_variant_new_dictionary(&godvar_consumed_amount, &godict_consumed_amount);

        api_arg->godot_dictionary_set(pgodict_person_consumed, &godvar_person_name, &godvar_consumed_amount);
    }
}

void GetPersonSavedGodictFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgodict_person_saved, const godot_gdnative_core_api_struct* api_arg)
{
    int i = 0;
    for (i = 0;i < pstr_scenario_info->saved_options.n_num_persons;i++)
    {
        wchar_t* pwchar_person_name = pstr_scenario_info->saved_options.person_option_amounts[i].name_person.wc_name;
        int size = wcslen(pwchar_person_name);
        godot_string godstring_person_name;
        api_arg->godot_string_new_with_wide_string(&godstring_person_name, pwchar_person_name, size);
        godot_variant godvar_person_name;
        api_arg->godot_variant_new_string(&godvar_person_name, &godstring_person_name);

        godot_dictionary godict_saved_amount;
        api_arg->godot_dictionary_new(&godict_saved_amount);
        GetSavedAmountGodictFromAdjustPriceResults(pstr_scenario_info, &godict_saved_amount, i, api_arg);

        godot_variant godvar_saved_amount;
        api_arg->godot_variant_new_dictionary(&godvar_saved_amount, &godict_saved_amount);

        api_arg->godot_dictionary_set(pgodict_person_saved, &godvar_person_name, &godvar_saved_amount);
    }
}


void GetGodotDictionaryFromAdjustPriceResults(struct strAdjustPriceResults* pstr_scenario_info, godot_dictionary* pgdict_results_scenario_info, const godot_gdnative_core_api_struct* api_arg)
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

    GetProductPriceGodictFromAdjustPriceResults(pstr_scenario_info, &godict_product_price, api_arg);

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

    GetPersonProdamountGodictFromAdjustPriceResults(pstr_scenario_info, &godict_person_prodamount, api_arg);

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

    GetPersonTradedGodictFromAdjustPriceResults(pstr_scenario_info, &godict_person_traded, api_arg);

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


    //////////////
    //Save Consumed:
    godot_dictionary godict_person_consumed;
    api_arg->godot_dictionary_new(&godict_person_consumed);

    GetPersonConsumedGodictFromAdjustPriceResults(pstr_scenario_info, &godict_person_consumed, api_arg);

    wchar_t* pwchar_consumed = L"Consumed";
    int size_consumed = wcslen(pwchar_consumed);
    godot_string godstring_consumed;
    api_arg->godot_string_new_with_wide_string(&godstring_consumed, pwchar_consumed, size_consumed);
    godot_variant godvar_consumed;
    api_arg->godot_variant_new_string(&godvar_consumed, &godstring_consumed);

    godot_variant godvar_person_consumed;
    api_arg->godot_variant_new_dictionary(&godvar_person_consumed, &godict_person_consumed);

    //Se añade el diccionario de consumed al diccionario del escenario
    api_arg->godot_dictionary_set(&godict_scenario_info, &godvar_consumed, &godvar_person_consumed);


    //////////////
    //Save Saved:
    godot_dictionary godict_person_saved;
    api_arg->godot_dictionary_new(&godict_person_saved);

    GetPersonSavedGodictFromAdjustPriceResults(pstr_scenario_info, &godict_person_saved, api_arg);

    wchar_t* pwchar_saved = L"Saved";
    int size_saved = wcslen(pwchar_saved);
    godot_string godstring_saved;
    api_arg->godot_string_new_with_wide_string(&godstring_saved, pwchar_saved, size_saved);
    godot_variant godvar_saved;
    api_arg->godot_variant_new_string(&godvar_saved, &godstring_saved);

    godot_variant godvar_person_saved;
    api_arg->godot_variant_new_dictionary(&godvar_person_consumed, &godict_person_consumed);

    //Se añade el diccionario de consumed al diccionario del escenario
    api_arg->godot_dictionary_set(&godict_scenario_info, &godvar_consumed, &godvar_person_consumed);



    //TODO
}
