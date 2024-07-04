#pragma once

#include <map>
#include <set>
#include <string>


struct strPreferencesCpp
{
    std::map<std::string, double> mapOptionMaxSatisf;
    std::map<std::string, double> mapOptionPrefAt0;
};

class CAdjustPrices 
{
public:
    CAdjustPrices() {}
    ~CAdjustPrices() {}

public:
    void add_person(wchar_t wc_person[256], int n_size);
    void add_product(wchar_t wc_product[256], int n_size);
    void add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
    void add_saving_option(wchar_t wc_saving_option[256], int n_size);
    void add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
    void add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
    void add_currency(wchar_t wc_currency[256], int n_size);
    void add_preferences_for_person(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);

    void ResetAdjustPricesDataInput();

public:
    std::set<std::string>& GetPersons() {
        return g_setPersons;
    }

    std::set<std::string>& GetProducts() {
        return g_setProducts;
    }

    std::set<std::string>& GetConsumptionOptions() {
        return g_setConsumptionOptions;
    }

    std::set<std::string>& GetSavingOptions() {
        return g_setSavingOptions;
    }

    std::map<std::string, std::map<std::string, double> >& GetMapPerson_ProdAmount() {
        return g_mapPerson_ProdAmount;
    }

    std::map<std::string, std::string>& GetMapOption_Product() {
        return g_mapOptionProduct;
    }

    std::string GetCurrency()& {
        return g_sCurrency;
    }

    std::map<std::string, strPreferencesCpp>& GetMapPerson_Preferences() {
        return g_mapPerson_Preferences;
    }

private:
    std::set<std::string> g_setPersons;
    std::set<std::string> g_setProducts;
    std::set<std::string> g_setConsumptionOptions;
    std::set<std::string> g_setSavingOptions;
    std::map<std::string, std::map<std::string, double> > g_mapPerson_ProdAmount;
    std::map<std::string, std::string> g_mapOptionProduct;
    std::string g_sCurrency;
    
    std::map<std::string, strPreferencesCpp> g_mapPerson_Preferences;
        
};



