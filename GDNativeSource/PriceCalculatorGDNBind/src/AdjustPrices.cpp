#include "AdjustPrices.h"

#include <codecvt>

void CAdjustPrices::add_person(wchar_t wc_person[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_person);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sPerson = converter.to_bytes(wide_str);

    g_setPersons.insert(sPerson);
}

void CAdjustPrices::add_product(wchar_t wc_product[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_product);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sProduct = converter.to_bytes(wide_str);

    g_setProducts.insert(sProduct);
}

void CAdjustPrices::add_consumption_option(wchar_t wc_consumption_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_consumption_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sConsumptionOption = converter.to_bytes(wide_str);

    g_setConsumptionOptions.insert(sConsumptionOption);
}

void CAdjustPrices::add_saving_option(wchar_t wc_saving_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_saving_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sSavingOption = converter.to_bytes(wide_str);

    g_setSavingOptions.insert(sSavingOption);
}

void CAdjustPrices::add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount)
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

void CAdjustPrices::add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product)
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

void CAdjustPrices::add_currency(wchar_t wc_currency[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str_currency(wc_currency);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sCurrency = converter.to_bytes(wide_str_currency);

    g_sCurrency = sCurrency;
}

void CAdjustPrices::add_preferences_for_person(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0)
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