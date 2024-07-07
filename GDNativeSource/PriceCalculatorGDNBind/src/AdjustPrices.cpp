#include "AdjustPrices.h"
#include "BindToCPP.h"
#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"

#include <codecvt>
#include <assert.h>
#include <iostream>

void CAdjustPrices::AddPerson(wchar_t wc_person[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_person);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sPerson = converter.to_bytes(wide_str);

    g_setPersons.insert(sPerson);
}

void CAdjustPrices::AddProduct(wchar_t wc_product[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_product);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sProduct = converter.to_bytes(wide_str);

    g_setProducts.insert(sProduct);
}

void CAdjustPrices::AddConsumptionOption(wchar_t wc_consumption_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_consumption_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sConsumptionOption = converter.to_bytes(wide_str);

    g_setConsumptionOptions.insert(sConsumptionOption);
}

void CAdjustPrices::AddSavingOption(wchar_t wc_saving_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_saving_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sSavingOption = converter.to_bytes(wide_str);

    g_setSavingOptions.insert(sSavingOption);
}

void CAdjustPrices::AddPersonOwned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount)
{
    std::map<std::string, double> mapProdAmount;

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sProduct = converter.to_bytes(wc_product);

    mapProdAmount[sProduct] = dAmount;
    std::string sPerson = converter.to_bytes(wc_person);

    if (g_mapPerson_ProdAmount.end() == g_mapPerson_ProdAmount.find(sPerson))
        g_mapPerson_ProdAmount[sPerson] = mapProdAmount;
    else
    {
        g_mapPerson_ProdAmount[sPerson][sProduct] = dAmount;
    }
}

void CAdjustPrices::AddOptionProduct(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str_option(wc_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sOption = converter.to_bytes(wide_str_option);

    // Convert wchar_t array to std::wstring
    std::wstring wide_str_product(wc_product);

    // Convert std::wstring to std::string    
    std::string sProduct = converter.to_bytes(wide_str_product);

    g_mapOptionProduct[sOption] = sProduct;
}

void CAdjustPrices::AddCurrency(wchar_t wc_currency[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str_currency(wc_currency);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sCurrency = converter.to_bytes(wide_str_currency);

    g_sCurrency = sCurrency;
}

void CAdjustPrices::AddPreferencesForPerson(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str_option(wc_option);
    std::wstring wide_str_person(wc_person);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sOption = converter.to_bytes(wide_str_option);
    std::string sPerson = converter.to_bytes(wide_str_person);

    //strPreferencesCpp strPref;    
    //strPref.mapOptionMaxSatisf[sOption] = d_maximum_satisfaction;
    //strPref.mapOptionPrefAt0[sOption] = d_preference_at_0;

    if (g_mapPerson_Preferences.end() == g_mapPerson_Preferences.find(sPerson))
        g_mapPerson_Preferences[sPerson];

    g_mapPerson_Preferences[sPerson].mapOptionMaxSatisf[sOption] = d_maximum_satisfaction;
    g_mapPerson_Preferences[sPerson].mapOptionPrefAt0[sOption] = d_preference_at_0;

}

void CAdjustPrices::ResetAdjustPricesDataInput()
{
    g_setPersons.clear();
    g_setProducts.clear();
    g_setConsumptionOptions.clear();
    g_setSavingOptions.clear();
    g_mapPerson_ProdAmount.clear();
    g_mapOptionProduct.clear();
    g_sCurrency.clear();
    g_mapPerson_Preferences.clear();
    
}

void CAdjustPrices::LoadResultsFromPriceCalculatorToStruct(pca::CPriceCalculator* pPriceCalculator, struct strAdjustPriceResults* pstrAdjustPriceResults)
{
    //Voy a meter la mayor parte de la lógica dentro de AdjustPrices
    //oAdjustPrices.LoadResultsFromPriceCalculatorToStruct(pPriceCalculator, pstrAdjustPriceResults);

    //int index = 0;

    //for (auto& person : g_setPersons)
    for (auto& person : this->GetPersons())

    {
        AddPersonToAdjustPriceResults_cpp(pstrAdjustPriceResults, person);
    }

    //for (auto& product : g_setProducts)
    for (auto& product : this->GetProducts())
    {
        double dPrice = pPriceCalculator->GetPrice(product);
        AddPriceToAdjustPriceResults_cpp(pstrAdjustPriceResults, product, dPrice);
    }

    //for (auto& consumption_option : g_setConsumptionOptions)
    for (auto& consumption_option : this->GetConsumptionOptions())
    {
        AddConsumptionOptionToAdjustPriceResults_cpp(pstrAdjustPriceResults, consumption_option);
    }

    //for (auto& saving_option : g_setSavingOptions)
    for (auto& saving_option : this->GetSavingOptions())
    {
        AddSavingOptionToAdjustPriceResults_cpp(pstrAdjustPriceResults, saving_option);
    }

    int person_index = 0;
    //for (auto& person : g_setPersons)
    for (auto& person : this->GetPersons())
    {
        //for (auto& product : g_setProducts)
        for (auto& product : this->GetProducts())
        {
            double dAmount = pPriceCalculator->GetProductAmount(product, person);
            AddOwnedThingToAdjustPriceResults_cpp(pstrAdjustPriceResults, person_index, person, product, dAmount);
        }
        person_index++;
    }


    //            
    //TODO. Seguir aquí.
    //void add_traded_thing_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
    //void add_consumed_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    //void add_saved_option_to_adjust_price_results_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    person_index = 0;
    //for (auto& person : g_setPersons)
    for (auto& person : this->GetPersons())
    {
        //for (auto& product : g_setProducts)
        for (auto& product : this->GetProducts())
        {
            double dAmount = pPriceCalculator->GetTradedAmount(product, person);
            AddTradedThingToAdjustPriceResults_cpp(pstrAdjustPriceResults, person_index, person, product, dAmount);
        }
        person_index++;
    }

    person_index = 0;
    //for (auto& sPerson : g_setPersons)
    for (auto& sPerson : this->GetPersons())
    {
        //for (auto& sOption : g_setSavingOptions)
        for (auto& sOption : this->GetSavingOptions())
        {
            double dAmount = pPriceCalculator->GetOptionAmount(sOption, sPerson);
            AddSavedOptionToAdjustPriceResults_cpp(pstrAdjustPriceResults, person_index, sPerson, sOption, dAmount);
        }
        //for (auto& sOption : g_setConsumptionOptions)
        for (auto& sOption : this->GetConsumptionOptions())
        {
            double dAmount = pPriceCalculator->GetOptionAmount(sOption, sPerson);
            AddConsumedOptionToAdjustPriceResults_cpp(pstrAdjustPriceResults, person_index, sPerson, sOption, dAmount);
        }
        person_index++;
    }


}


void CAdjustPrices::AddPersonToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrAdjustPriceResults->name_persons[pstrAdjustPriceResults->n_num_of_persons].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->n_num_of_persons += 1;
}

void CAdjustPrices::AddPersonToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sPerson)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);

    wchar_t array_wc_not_const[256];
    int size = ws_person_name.size();
    wcsncpy(array_wc_not_const, ws_person_name.c_str(), size);

    AddPersonToAdjustPriceResults(pstrAdjustPriceResults, array_wc_not_const, size);
}

void CAdjustPrices::AddProductToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrAdjustPriceResults->name_products[pstrAdjustPriceResults->n_num_of_products].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->n_num_of_products += 1;
}

void CAdjustPrices::AddProductToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_not_const[256];
    int size = ws_product_name.size();
    wcsncpy(array_wc_not_const, ws_product_name.c_str(), size);

    AddProductToAdjustPriceResults(pstrAdjustPriceResults, array_wc_not_const, size);
}

void CAdjustPrices::AddConsumptionOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrAdjustPriceResults->name_consumption_options[pstrAdjustPriceResults->n_num_of_consumption_options].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->n_num_of_consumption_options += 1;
}

void CAdjustPrices::AddConsumptionOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_not_const[256];
    int size = ws_option_name.size();
    wcsncpy(array_wc_not_const, ws_option_name.c_str(), size);

    AddConsumptionOptionToAdjustPriceResults(pstrAdjustPriceResults, array_wc_not_const, size);
}

void CAdjustPrices::AddSavingOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrAdjustPriceResults->name_saving_options[pstrAdjustPriceResults->n_num_of_saving_options].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->n_num_of_saving_options += 1;
}

void CAdjustPrices::AddSavingOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_not_const[256];
    int size = ws_option_name.size();
    wcsncpy(array_wc_not_const, ws_option_name.c_str(), size);

    AddSavingOptionToAdjustPriceResults(pstrAdjustPriceResults, array_wc_not_const, size);
}

void CAdjustPrices::AddOwnedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount)
{
    //int person_index = pstrAdjustPriceResults->owned_things.n_num_persons;
    int prod_amount_index = pstrAdjustPriceResults->owned_things.person_prod_amounts[person_index].n_num_prod_amounts;

    wchar_t* pwc_person_name_in_struct = pstrAdjustPriceResults->owned_things.person_prod_amounts[person_index].name_person.wc_name;
    wchar_t* pwc_product_name_in_struct = pstrAdjustPriceResults->owned_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].name_product.wc_name;

    wcsncpy(pwc_person_name_in_struct, wc_person, size_person);
    //pwc_person_name_in_struct[size_person - 1] = L'\0';  // Ensure null-termination

    wcsncpy(pwc_product_name_in_struct, wc_product, size_product);
    //pwc_product_name_in_struct[size_product - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->owned_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].dAmount = dAmount;

    if (pstrAdjustPriceResults->owned_things.n_num_persons < person_index + 1)
    {
        pstrAdjustPriceResults->owned_things.n_num_persons = person_index + 1;
    }

    pstrAdjustPriceResults->owned_things.person_prod_amounts[person_index].n_num_prod_amounts += 1;
}

void CAdjustPrices::AddOwnedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_person_not_const[256];
    wchar_t array_wc_product_not_const[256];
    int size_person = ws_person_name.size();
    int size_product = ws_product_name.size();
    wcsncpy(array_wc_person_not_const, ws_person_name.c_str(), size_person);
    wcsncpy(array_wc_product_not_const, ws_product_name.c_str(), size_product);

    AddOwnedThingToAdjustPriceResults(pstrAdjustPriceResults, person_index, array_wc_person_not_const, size_person, array_wc_product_not_const, size_product, dAmount);
}

void CAdjustPrices::AddPriceToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_product[256], int size, double dPrice)
{
    int prod_price_index = pstrAdjustPriceResults->prices.n_num_prices;

    wchar_t* pwc_product_name_in_struct = pstrAdjustPriceResults->prices.prod_price[prod_price_index].name_product.wc_name;

    wcsncpy(pwc_product_name_in_struct, wc_product, size);
    //pwc_product_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrAdjustPriceResults->prices.prod_price[prod_price_index].dAmount = dPrice;

    pstrAdjustPriceResults->prices.n_num_prices += 1;
}

void CAdjustPrices::AddPriceToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct, double dPrice)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_not_const[256];
    int size = ws_product_name.size();
    wcsncpy(array_wc_not_const, ws_product_name.c_str(), size);

    AddPriceToAdjustPriceResults(pstrAdjustPriceResults, array_wc_not_const, size, dPrice);

}

//Nuevos
void CAdjustPrices::AddTradedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount)
{
    int prod_amount_index = pstrAdjustPriceResults->traded_things.person_prod_amounts[person_index].n_num_prod_amounts;

    wchar_t* pwc_person_name_in_struct = pstrAdjustPriceResults->traded_things.person_prod_amounts[person_index].name_person.wc_name;
    wchar_t* pwc_product_name_in_struct = pstrAdjustPriceResults->traded_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].name_product.wc_name;

    wcsncpy(pwc_person_name_in_struct, wc_person, size_person);
    wcsncpy(pwc_product_name_in_struct, wc_product, size_product);

    pstrAdjustPriceResults->traded_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].dAmount = dAmount;

    if (pstrAdjustPriceResults->traded_things.n_num_persons < person_index + 1)
    {
        pstrAdjustPriceResults->traded_things.n_num_persons = person_index + 1;
    }

    pstrAdjustPriceResults->traded_things.person_prod_amounts[person_index].n_num_prod_amounts += 1;
}

void CAdjustPrices::AddTradedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_person_not_const[256];
    wchar_t array_wc_product_not_const[256];
    int size_person = ws_person_name.size();
    int size_product = ws_product_name.size();
    wcsncpy(array_wc_person_not_const, ws_person_name.c_str(), size_person);
    wcsncpy(array_wc_product_not_const, ws_product_name.c_str(), size_product);

    AddTradedThingToAdjustPriceResults(pstrAdjustPriceResults, person_index, array_wc_person_not_const, size_person, array_wc_product_not_const, size_product, dAmount);
}

void CAdjustPrices::AddConsumedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount)
{

    int option_amount_index = pstrAdjustPriceResults->consumed_options.person_option_amounts[person_index].n_num_option_amounts;

    wchar_t* pwc_person_name_in_struct = pstrAdjustPriceResults->consumed_options.person_option_amounts[person_index].name_person.wc_name;
    wchar_t* pwc_option_name_in_struct = pstrAdjustPriceResults->consumed_options.person_option_amounts[person_index].option_amounts[option_amount_index].name_option.wc_name;

    wcsncpy(pwc_person_name_in_struct, wc_person, size_person);
    wcsncpy(pwc_option_name_in_struct, wc_option, size_option);

    pstrAdjustPriceResults->consumed_options.person_option_amounts[person_index].option_amounts[option_amount_index].dAmount = dAmount;

    if (pstrAdjustPriceResults->consumed_options.n_num_persons < person_index + 1)
    {
        pstrAdjustPriceResults->consumed_options.n_num_persons = person_index + 1;
    }

    pstrAdjustPriceResults->consumed_options.person_option_amounts[person_index].n_num_option_amounts += 1;

}

void CAdjustPrices::AddConsumedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount)
{

    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_person_not_const[256];
    wchar_t array_wc_option_not_const[256];
    int size_person = ws_person_name.size();
    int size_option = ws_option_name.size();
    wcsncpy(array_wc_person_not_const, ws_person_name.c_str(), size_person);
    wcsncpy(array_wc_option_not_const, ws_option_name.c_str(), size_option);

    AddConsumedOptionToAdjustPriceResults(pstrAdjustPriceResults, person_index, array_wc_person_not_const, size_person, array_wc_option_not_const, size_option, dAmount);

}

void CAdjustPrices::AddSavedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount)
{
    int option_amount_index = pstrAdjustPriceResults->saved_options.person_option_amounts[person_index].n_num_option_amounts;

    wchar_t* pwc_person_name_in_struct = pstrAdjustPriceResults->saved_options.person_option_amounts[person_index].name_person.wc_name;
    wchar_t* pwc_option_name_in_struct = pstrAdjustPriceResults->saved_options.person_option_amounts[person_index].option_amounts[option_amount_index].name_option.wc_name;

    wcsncpy(pwc_person_name_in_struct, wc_person, size_person);
    wcsncpy(pwc_option_name_in_struct, wc_option, size_option);

    pstrAdjustPriceResults->saved_options.person_option_amounts[person_index].option_amounts[option_amount_index].dAmount = dAmount;

    if (pstrAdjustPriceResults->saved_options.n_num_persons < person_index + 1)
    {
        pstrAdjustPriceResults->saved_options.n_num_persons = person_index + 1;
    }

    pstrAdjustPriceResults->saved_options.person_option_amounts[person_index].n_num_option_amounts += 1;
}

void CAdjustPrices::AddSavedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount)
{

    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_person_not_const[256];
    wchar_t array_wc_option_not_const[256];
    int size_person = ws_person_name.size();
    int size_option = ws_option_name.size();
    wcsncpy(array_wc_person_not_const, ws_person_name.c_str(), size_person);
    wcsncpy(array_wc_option_not_const, ws_option_name.c_str(), size_option);

    AddSavedOptionToAdjustPriceResults(pstrAdjustPriceResults, person_index, array_wc_person_not_const, size_person, array_wc_option_not_const, size_option, dAmount);
}

void CAdjustPrices::LoadInputDataIntoPriceCalculatorAndAdjustPrices(pca::CPriceCalculator* pPriceCalculator)
{
    pPriceCalculator->CreateEmptyReality();
    //for (auto& product : g_setProducts)
    for (auto& product : this->GetProducts())
    {
        pPriceCalculator->CreateProduct(product);
    }

    //for (auto& pairOptionProduct : g_mapOptionProduct)
    for (auto& pairOptionProduct : this->GetMapOption_Product())
    {
        pPriceCalculator->AddToProduct_CreateConsumptionOption(pairOptionProduct.second, pairOptionProduct.first);
    }

    pPriceCalculator->CreateEmptyMarket();

    //pPriceCalculator->SetCurrency(g_sCurrency);
    pPriceCalculator->SetCurrency(this->GetCurrency());

    //for (auto& person : g_setPersons)
    for (auto& person : this->GetPersons())
    {
        pPriceCalculator->AddToMarket_CreatePerson(person);
    }

    //for (auto& pairperson_prodamounts : g_mapPerson_ProdAmount)
    for (auto& pairperson_prodamounts : this->GetMapPerson_ProdAmount())
    {
        std::string person = pairperson_prodamounts.first;
        std::map<std::string, double> mapProd_Amount = pairperson_prodamounts.second;

        for (auto& pairProd_Amount : mapProd_Amount)
        {
            std::string product = pairProd_Amount.first;
            double dAmount = pairProd_Amount.second;

            pPriceCalculator->AddToPerson_SetProductAmount(person, product, dAmount);
        }
    }

    //for (auto& person : g_setPersons)
    //{        
    //    std::set<std::string> setOptions = g_setConsumptionOptions;
    //    setOptions.insert(g_setSavingOptions.begin(), g_setSavingOptions.end());

    //    for (auto& option : setOptions)
    //    {
    //        //TODO: añadir la configuración de esto
    //        double dValueAt0 = 1;
    //        double dMaxValue = 10;

    //        pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption(person, option, dValueAt0, dMaxValue);
    //    }
    //}

    //for (auto& pairPerson_Pref : g_mapPerson_Preferences)
    for (auto& pairPerson_Pref : this->GetMapPerson_Preferences())
    {
        std::string sPerson = pairPerson_Pref.first;
        strPreferencesCpp strPref = pairPerson_Pref.second;

        for (auto& pairOption_dMaxSat : strPref.mapOptionMaxSatisf)
        {
            std::string sOption = pairOption_dMaxSat.first;
            double dMaxSatisf = pairOption_dMaxSat.second;

            if (strPref.mapOptionPrefAt0.end() == strPref.mapOptionPrefAt0.find(sOption))
            {
                std::cerr << "Error en LaunchPriceCalculatorLoadedScenario";
                assert("" == "Error en LaunchPriceCalculatorLoadedScenario");
            }

            double dPrefAt0 = strPref.mapOptionPrefAt0.at(sOption);

            pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption(sPerson, sOption, dPrefAt0, dMaxSatisf);
        }
    }


    pPriceCalculator->AdjustPrices();

}


void CAdjustPrices::AdjustPriceWithPriceCalculator(pca::CPriceCalculator* pPriceCalculator, struct strAdjustPriceResults* pstrAdjustPriceResults)
{
    //Método para cargar los datos del escenario a calcular en CPriceCalculator y calcular los precios
    LoadInputDataIntoPriceCalculatorAndAdjustPrices(pPriceCalculator);

    //Poner la estructura a 0, por si no se ha inicializado antes
    struct strAdjustPriceResults emptyStruct = { 0 };
    *pstrAdjustPriceResults = emptyStruct;
    //Método para guardar los resultados de PriceCalculator en una estructura compatible con C:
    LoadResultsFromPriceCalculatorToStruct(pPriceCalculator, pstrAdjustPriceResults);


}