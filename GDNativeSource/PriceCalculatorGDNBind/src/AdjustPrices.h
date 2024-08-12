#pragma once

#include <map>
#include <set>
#include <string>

namespace pca{
    class CPriceCalculator;
}

//Estructura con el output para Godot
struct strAdjustPriceResults;


//Clase para manejar el input y output de PriceCalculator
class CAdjustPrices 
{
public:
    struct strPreferencesCpp
    {
        std::map<std::string, double> mapOptionMaxSatisf;
        std::map<std::string, double> mapOptionPrefAt0;
    };


public:
    CAdjustPrices() {}
    ~CAdjustPrices() {}

public:

    //Metodos para definir el escenario (input) que se quiere calcular
    void AddPerson(wchar_t wc_person[256], int n_size);
    void AddProduct(wchar_t wc_product[256], int n_size);
    void AddConsumptionOption(wchar_t wc_consumption_option[256], int n_size);
    void AddSavingOption(wchar_t wc_saving_option[256], int n_size);
    void AddPersonOwned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
    void AddOptionProduct(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
    void AddCurrency(wchar_t wc_currency[256], int n_size);
    void AddPreferencesForPerson(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);
    void AddComplementaryCombo(wchar_t wc_compl_combo[256], int n_size_compl_combo);
    void AddOptionToComplementaryCombo(wchar_t wc_compl_combo[256], int n_size_compl_combo, wchar_t wc_option[256], int n_size_option);
    void AddSupplementaryCombo(wchar_t wc_suppl_combo[256], int n_size_suppl_combo);
    void AddOptionToSupplementaryCombo(wchar_t wc_suppl_combo[256], int n_size_suppl_combo, wchar_t wc_option[256], int n_size_option, double dWeight);

    //Método para resetear el escenario que se quiere calcular
    void ResetAdjustPricesDataInput();

    //Método para cargar los datos (input) del escenario a calcular en CPriceCalculator y calcular los precios y guardarlos (output) en la estructura strAdjustPriceResults
    void AdjustPriceWithPriceCalculator(pca::CPriceCalculator* pPriceCalculator, struct strAdjustPriceResults* pstrAdjustPriceResults);


protected:
    //Método para cargar los datos del escenario a calcular en CPriceCalculator y calcular los precios
    void LoadInputDataIntoPriceCalculatorAndAdjustPrices(pca::CPriceCalculator* pPriceCalculator);

    //Método para guardar los resultados (output) de PriceCalculator en una estructura compatible con C:
    void LoadResultsFromPriceCalculatorToStruct(pca::CPriceCalculator* pPriceCalculator, struct strAdjustPriceResults* pstrAdjustPriceResults);

    //Métodos auxiliares para guardar los resultados de PriceCalculator en una estructura compatible con C:
    static void AddPersonToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sPerson);
    static void AddProductToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct);
    static void AddConsumptionOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
    static void AddSavingOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
    static void AddOwnedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
    static void AddPriceToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct, double dPrice);
    static void AddTradedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
    static void AddConsumedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    static void AddSavedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    static void AddPersonToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    static void AddProductToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    static void AddConsumptionOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    static void AddSavingOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    static void AddOwnedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
    static void AddPriceToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_product[256], int size, double dPrice);
    static void AddTradedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
    static void AddConsumedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);
    static void AddSavedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);



protected:

    //Métodos Get de acceso a variables miembro
    std::set<std::string>& GetPersons() {
        return m_setPersons;
    }

    std::set<std::string>& GetProducts() {
        return m_setProducts;
    }

    std::set<std::string>& GetConsumptionOptions() {
        return m_setConsumptionOptions;
    }

    std::set<std::string>& GetSavingOptions() {
        return m_setSavingOptions;
    }

    std::map<std::string, std::map<std::string, double> >& GetMapPerson_ProdAmount() {
        return m_mapPerson_ProdAmount;
    }

    std::map<std::string, std::string>& GetMapOption_Product() {
        return m_mapOptionProduct;
    }

    std::string GetCurrency()& {
        return m_sCurrency;
    }

    std::map<std::string, strPreferencesCpp>& GetMapPerson_Preferences() {
        return m_mapPerson_Preferences;
    }

private:

    //Variables miembro con el Input para PriceCalculator
    std::set<std::string> m_setPersons;
    std::set<std::string> m_setProducts;
    std::set<std::string> m_setConsumptionOptions;
    std::set<std::string> m_setSavingOptions;
    std::map<std::string, std::map<std::string, double> > m_mapPerson_ProdAmount;
    std::map<std::string, std::string> m_mapOptionProduct;
    
    std::map<std::string, std::set<std::string>> m_mapComplCombo_Options;
    std::map<std::string, std::map<std::string,double>> m_mapSupplCombo_mapOptionWeight;
    

    std::string m_sCurrency;
    
    std::map<std::string, strPreferencesCpp> m_mapPerson_Preferences;
        
};



