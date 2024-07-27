#pragma once

#include <map>
#include <set>
#include <string>

namespace pca{
    class CPriceCalculator;
    class CTradeCalculatorScenario;
}

//Estructura con el output para Godot
struct strAdjustBestCombinationResults;


//Clase para manejar el input y output de PriceCalculator
class CAdjustBestCombination 
{
public:
    struct strPreferencesCpp
    {
        std::map<std::string, double> mapOptionMaxSatisf;
        std::map<std::string, double> mapOptionPrefAt0;

        void Clear() {
            mapOptionMaxSatisf.clear();
            mapOptionPrefAt0.clear();
        }
    };


public:
    CAdjustBestCombination() {}
    ~CAdjustBestCombination() {}

public:


    //Metodos para definir el escenario (input) que se quiere calcular
    // 
    void AddBudget(double dBudget);

    //void AddPerson(wchar_t wc_person[256], int n_size);
    void AddProduct(wchar_t wc_product[256], int n_size);
    void AddConsumptionOption(wchar_t wc_consumption_option[256], int n_size);
    void AddSavingOption(wchar_t wc_saving_option[256], int n_size);
    //void AddPersonOwned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
    void AddOptionProduct(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
    void AddCurrency(wchar_t wc_currency[256], int n_size);
    void AddPreferences(wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);

    //Método para resetear el escenario que se quiere calcular
    void ResetAdjustBestCombinationDataInput();

    //Método para cargar los datos (input) del escenario a calcular en CPriceCalculator y calcular los precios y guardarlos (output) en la estructura strAdjustPriceResults
    void AdjustBestCombinationWithPriceCalculator(pca::CTradeCalculatorScenario* pTradeCalculatorScenario, struct strAdjustBestCombinationResults* pstrAdjustPriceResults);


protected:
    //Método para cargar los datos del escenario a calcular en CPriceCalculator y calcular los precios
    std::map<std::string, double> LoadInputDataIntoPriceCalculatorAndAdjustBestCombination(pca::CTradeCalculatorScenario* pTradeCalculatorScenario);

    //Método para guardar los resultados (output) de PriceCalculator en una estructura compatible con C:
    void LoadResultsFromPriceCalculatorToStruct(std::map<std::string, double> mapBestCombinationOption_dAmount, struct strAdjustBestCombinationResults* pstrAdjustPriceResults);

    //Métodos auxiliares para guardar los resultados de PriceCalculator en una estructura compatible con C:
    //static void AddPersonToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sPerson);
    //static void AddProductToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct);
    //static void AddConsumptionOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
    //static void AddSavingOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sOption);
    //static void AddOwnedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
    //static void AddPriceToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, std::string sProduct, double dPrice);
    //static void AddTradedThingToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sProduct, double dAmount);
    //static void AddConsumedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    //static void AddSavedOptionToAdjustPriceResults_cpp(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, std::string sPerson, std::string sOption, double dAmount);
    //static void AddPersonToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    //static void AddProductToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    //static void AddConsumptionOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    //static void AddSavingOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_name[256], int size);
    //static void AddOwnedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
    //static void AddPriceToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, wchar_t wc_product[256], int size, double dPrice);
    //static void AddTradedThingToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
    //static void AddConsumedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);
    //static void AddSavedOptionToAdjustPriceResults(struct strAdjustPriceResults* pstrAdjustPriceResults, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);



protected:

    ////Métodos Get de acceso a variables miembro
    // 
    double GetBudget() {
        return m_dBudget;
    }
    //std::set<std::string>& GetPersons() {
    //    return g_setPersons;
    //}

    std::set<std::string>& GetProducts() {
        return m_setProducts;
    }

    std::set<std::string>& GetConsumptionOptions() {
        return m_setConsumptionOptions;
    }

    std::set<std::string>& GetSavingOptions() {
        return m_setSavingOptions;
    }

    //std::map<std::string, std::map<std::string, double> >& GetMapPerson_ProdAmount() {
    //    return g_mapPerson_ProdAmount;
    //}

    std::map<std::string, std::string>& GetMapOption_Product() {
        return m_mapOptionProduct;
    }

    std::string GetCurrency()& {
        return m_sCurrency;
    }

    //std::map<std::string, strPreferencesCpp>& GetMapPerson_Preferences() {
    //    return g_mapPerson_Preferences;
    //}

private:

    //Variables miembro con el Input para PriceCalculator
    // 
    double m_dBudget = 0.0;
    //std::set<std::string> g_setPersons;
    std::set<std::string> m_setProducts;
    std::set<std::string> m_setConsumptionOptions;
    std::set<std::string> m_setSavingOptions;
    //std::map<std::string, std::map<std::string, double> > g_mapPerson_ProdAmount;
    std::map<std::string, std::string> m_mapOptionProduct;
    std::string m_sCurrency;
    
    //std::map<std::string, strPreferencesCpp> g_mapPerson_Preferences;

    strPreferencesCpp m_strPreferencesCpp;
        
};



