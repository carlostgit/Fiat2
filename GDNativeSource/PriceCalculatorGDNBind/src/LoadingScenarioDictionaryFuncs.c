#include "LoadingScenarioDictionaryFuncs.h"
#include "BindToCPP.h"
#include "AuxFuncs.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////
//Inicio de métodos para procesar la información que llega desde GODOT

void ProcessScenarioPersons(godot_array* pgodarray_persons_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_array godarray_persons = (*pgodarray_persons_arg);

    godot_int godint_size_of_array = api_arg->godot_array_size(&godarray_persons);

    printf("Size of array: %d \n", godint_size_of_array);

    int i = 0;
    for (i = 0;i < godint_size_of_array;i++)
    {
        godot_variant godvar_person;
        godvar_person = api_arg->godot_array_get(&godarray_persons, i);

        godot_string godstring_person = api_arg->godot_variant_as_string(&godvar_person);

        wchar_t* wc_person = api_arg->godot_string_wide_str(&godstring_person);

        add_person(wc_person, 256);
    }
}

void ProcessScenarioProducts(godot_array* pgodarray_products_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_array godarray_products = (*pgodarray_products_arg);

    godot_int godint_size_of_array = api_arg->godot_array_size(&godarray_products);

    printf("Size of array: %d \n", godint_size_of_array);

    int i = 0;
    for (i = 0;i < godint_size_of_array;i++)
    {
        godot_variant godvar_product;
        godvar_product = api_arg->godot_array_get(&godarray_products, i);

        godot_string godstring_product = api_arg->godot_variant_as_string(&godvar_product);

        wchar_t* wc_product = api_arg->godot_string_wide_str(&godstring_product);

        add_product(wc_product, 256);
    }
}

void ProcessScenarioConsumption(godot_array* pgodarray_consumption_options_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_array godarray_consumption_options = (*pgodarray_consumption_options_arg);

    godot_int godint_size_of_array = api_arg->godot_array_size(&godarray_consumption_options);

    printf("Size of array: %d \n", godint_size_of_array);

    int i = 0;
    for (i = 0;i < godint_size_of_array;i++)
    {
        godot_variant godvar_consumption_option;
        godvar_consumption_option = api_arg->godot_array_get(&godarray_consumption_options, i);

        godot_string godstring_consumption_option = api_arg->godot_variant_as_string(&godvar_consumption_option);

        wchar_t* wc_consumption_option = api_arg->godot_string_wide_str(&godstring_consumption_option);

        add_consumption_option(wc_consumption_option, 256);
    }
}

void ProcessScenarioSaving(godot_array* pgodarray_saving_options_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_array godarray_saving_options = (*pgodarray_saving_options_arg);

    godot_int godint_size_of_array = api_arg->godot_array_size(&godarray_saving_options);

    printf("Size of array: %d \n", godint_size_of_array);

    int i = 0;
    for (i = 0;i < godint_size_of_array;i++)
    {
        godot_variant godvar_saving_option;
        godvar_saving_option = api_arg->godot_array_get(&godarray_saving_options, i);

        godot_string godstring_saving_option = api_arg->godot_variant_as_string(&godvar_saving_option);

        wchar_t* wc_saving_option = api_arg->godot_string_wide_str(&godstring_saving_option);

        add_saving_option(wc_saving_option, 256);
    }
}

void ProcessScenarioPersonOwned(godot_string* pgostring_person_arg, godot_dictionary* pgodict_product_amount_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_string gostring_person_arg = (*pgostring_person_arg);

    godot_dictionary godict_product_owned = (*pgodict_product_amount_arg);

    godot_array godarray_keys_products = api_arg->godot_dictionary_keys(&godict_product_owned);
    godot_array godarray_values_products = api_arg->godot_dictionary_values(&godict_product_owned);

    godot_int godint_size_of_array_products = api_arg->godot_array_size(&godarray_keys_products);

    printf("Size of array: %d \n", godint_size_of_array_products);

    int i = 0;
    for (i = 0;i < godint_size_of_array_products;i++)
    {
        godot_variant godvar_my_key;
        godvar_my_key = api_arg->godot_array_get(&godarray_keys_products, i);
        godot_string godstring_key_product = api_arg->godot_variant_as_string(&godvar_my_key);

        godot_variant godvar_my_value;
        godvar_my_value = api_arg->godot_array_get(&godarray_values_products, i);
        godot_real godreal_value = api_arg->godot_variant_as_real(&godvar_my_value);

        const wchar_t* pwc_person = api_arg->godot_string_wide_str(&gostring_person_arg);
        const wchar_t* pwc_product = api_arg->godot_string_wide_str(&godstring_key_product);
        float dAmountOfProduct = godreal_value;

        add_person_owned(pwc_person, 256, pwc_product, 256, dAmountOfProduct);
    }
}

void ProcessScenarioOwned(godot_dictionary* pgodict_owned_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_dictionary godict_owned = (*pgodict_owned_arg);

    godot_array godarray_keys_persons = api_arg->godot_dictionary_keys(&godict_owned);
    godot_array godarray_values_persons = api_arg->godot_dictionary_values(&godict_owned);

    godot_int godint_size_of_array_persons = api_arg->godot_array_size(&godarray_keys_persons);

    printf("Size of array: %d \n", godint_size_of_array_persons);

    int i = 0;
    for (i = 0;i < godint_size_of_array_persons;i++)
    {
        godot_variant godvar_my_key;
        godvar_my_key = api_arg->godot_array_get(&godarray_keys_persons, i);
        godot_string godstring_key_person = api_arg->godot_variant_as_string(&godvar_my_key);

        godot_variant godvar_my_value;
        godvar_my_value = api_arg->godot_array_get(&godarray_values_persons, i);
        godot_dictionary godict_value_prodamounts = api_arg->godot_variant_as_dictionary(&godvar_my_value);

        ProcessScenarioPersonOwned(&godstring_key_person, &godict_value_prodamounts, api_arg);
    }
}

void ProcessScenarioOptionProduct(godot_dictionary* pgodict_option_product_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_dictionary godict_option_product = (*pgodict_option_product_arg);

    godot_array godarray_keys_options = api_arg->godot_dictionary_keys(&godict_option_product);
    godot_array godarray_values_products = api_arg->godot_dictionary_values(&godict_option_product);

    godot_int godint_size_of_array_options = api_arg->godot_array_size(&godarray_keys_options);

    printf("Size of array: %d \n", godint_size_of_array_options);

    int i = 0;
    for (i = 0;i < godint_size_of_array_options;i++)
    {
        godot_variant godvar_my_key;
        godvar_my_key = api_arg->godot_array_get(&godarray_keys_options, i);
        godot_string godstring_key_option = api_arg->godot_variant_as_string(&godvar_my_key);

        godot_variant godvar_my_value;
        godvar_my_value = api_arg->godot_array_get(&godarray_values_products, i);
        godot_string godict_value_product = api_arg->godot_variant_as_string(&godvar_my_value);

        const wchar_t* pwc_option = api_arg->godot_string_wide_str(&godstring_key_option);
        const wchar_t* pwc_product = api_arg->godot_string_wide_str(&godict_value_product);

        add_option_product(pwc_option, 256, pwc_product, 256);
    }
}

void ProcessScenarioCurrency(godot_string* pgostring_currency_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_string gostring_currency = (*pgostring_currency_arg);
    const wchar_t* pwc_currency = api_arg->godot_string_wide_str(&gostring_currency);
    add_currency(pwc_currency, 256);
}

//Método para procesar la información del escenario que viene en un diccionario desde GODOT
void ProcessScenarioInfo(godot_dictionary* pgodict_scenario_info_arg, const godot_gdnative_core_api_struct* api_arg)
{
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
    //    "Currency" : "nut"
    //}

    //godot_dictionary godict_arg = api2->godot_variant_as_dictionary(p_args[i]);
    godot_dictionary godict_scenario_info = (*pgodict_scenario_info_arg);

    godot_array godarray_keys = api_arg->godot_dictionary_keys(&godict_scenario_info);
    godot_array godarray_values = api_arg->godot_dictionary_values(&godict_scenario_info);

    godot_int godint_size_of_array = api_arg->godot_array_size(&godarray_keys);

    printf("Size of array: %d \n", godint_size_of_array);

    int i = 0;
    for (i = 0;i < godint_size_of_array;i++)
    {
        //No sé si hace falta copiar los strings como lo hago aquí
        //No sé qué tipo de copia se hace con los variant, si paso la referencia directamente
        //desde el diccionario origen
        godot_variant godvar_my_key;
        godvar_my_key = api_arg->godot_array_get(&godarray_keys, i);
        godot_string godstring_key = api_arg->godot_variant_as_string(&godvar_my_key);
        api_arg->godot_print(&godstring_key);

        godot_variant godvar_my_value;
        godvar_my_value = api_arg->godot_array_get(&godarray_values, i);
        godot_string godstring_value = api_arg->godot_variant_as_string(&godvar_my_value);
        api_arg->godot_print(&godstring_value);

        const wchar_t* pwc_key = api_arg->godot_string_wide_str(&godstring_key);
        const wchar_t wc_persons[] = L"Persons";
        const wchar_t wc_products[] = L"Products";
        const wchar_t wc_consumption[] = L"Consumption";
        const wchar_t wc_saving[] = L"Saving";
        const wchar_t wc_owned[] = L"Owned";
        const wchar_t wc_option_product[] = L"OptionProduct";
        const wchar_t wc_currency[] = L"Currency";

        if (wcscmp(pwc_key, wc_persons) == 0)
        {
            godot_array godarray_persons = api_arg->godot_variant_as_array(&godvar_my_value);
            ProcessScenarioPersons(&godarray_persons, api_arg);
        }
        else if (wcscmp(pwc_key, wc_products) == 0)
        {
            godot_array godarray_products = api_arg->godot_variant_as_array(&godvar_my_value);
            ProcessScenarioProducts(&godarray_products, api_arg);
        }
        else if (wcscmp(pwc_key, wc_consumption) == 0)
        {
            godot_array godarray_consumption = api_arg->godot_variant_as_array(&godvar_my_value);
            ProcessScenarioConsumption(&godarray_consumption, api_arg);
        }
        else if (wcscmp(pwc_key, wc_saving) == 0)
        {
            godot_array godarray_saving = api_arg->godot_variant_as_array(&godvar_my_value);
            ProcessScenarioSaving(&godarray_saving, api_arg);
        }
        else if (wcscmp(pwc_key, wc_owned) == 0)
        {
            godot_dictionary godict_owned = api_arg->godot_variant_as_dictionary(&godvar_my_value);
            ProcessScenarioOwned(&godict_owned, api_arg);
        }
        else if (wcscmp(pwc_key, wc_option_product) == 0)
        {
            godot_dictionary godict_option_product = api_arg->godot_variant_as_dictionary(&godvar_my_value);
            ProcessScenarioOptionProduct(&godict_option_product, api_arg);
        }
        else if (wcscmp(pwc_key, wc_currency) == 0)
        {
            godot_string gostring_currency = api_arg->godot_variant_as_string(&godvar_my_value);
            ProcessScenarioCurrency(&gostring_currency, api_arg);
        }
    }
}
