#pragma once

//"BindToCPP.h" es una cabecera con las funciones y estructuras en código C,
//para que puedan ser usados desde el código GND, que está en en C.
// Son métodos que sirven para hacer las llamadas a PriceCalculator
// -Para pasar los datos del escenario que se quiere calcular
// -Y para recoger los resultados
//Los métodos de esta cabecera compatible con C están definidos en C++ en "BindToCPP.cpp"
//Existe otra cabecera con variables y métodos C++ (BindToCPP_CPPHeader.h)


//struct strProductAmount2
//{
//    int nProductId;
//    double dAmount;    
//};

//Estructuras con las que se devolverán los resultados a GDNBind
//
struct strName
{
    wchar_t wc_name[256];
};

struct strProductAmount
{
    struct strName name_product;
    double dAmount;
};

struct strOptionAmount
{
    struct strName name_option;
    double dAmount;
};

struct strOptionPreference
{
    struct strName name_option;
    double dPreferenceAt0;
    double dMaximumSatisfaction;
};

struct strPersonProductAmounts
{
    struct strName name_person;
    int n_num_prod_amounts;
    struct strProductAmount prod_amounts[25];
};

struct strPersonOptionAmounts
{
    struct strName name_person;
    int n_num_option_amounts;
    struct strOptionAmount option_amounts[25];
};

struct strPersonOptionPreferences
{
    struct strName name_person;
    int n_num_option_preferences;
    struct strOptionPreference option_preferences[25];
};

struct strOwnedThings
{
    int n_num_persons;
    struct strPersonProductAmounts person_prod_amounts[25];    
};

struct strTradedThings
{
    int n_num_persons;
    struct strPersonProductAmounts person_prod_amounts[25];
};

struct strPrices
{
    int n_num_prices;
    struct strProductAmount prod_price[25];
};

struct strConsumedOptions
{
    int n_num_persons;
    struct strPersonOptionAmounts person_option_amounts[25];
};

struct strSavedOptions
{
    int n_num_persons;
    struct strPersonOptionAmounts person_option_amounts[25];
};

struct strPreferences
{
    int n_num_persons;
    struct strPersonOptionPreferences person_option_preferences[25];
};


struct strScenarioInfo //TODO: Cambiar el nombre a esto a a algo así como strAdjustPriceResults
{
    struct strName name_persons[25];
    int n_num_of_persons;
    struct strName name_products[25];
    int n_num_of_products;
    struct strName name_consumption_options[25];
    int n_num_of_consumption_options;
    struct strName name_saving_options[25];
    int n_num_of_saving_options;
    //La parte de arriba tal vez se pueda omitir para los resultados, porque no debería cambiar respecto a los datos originales

    //Esto de abajo si sería parte de los resultados:
    struct strOwnedThings owned_things;
    struct strTradedThings traded_things; //new
    struct strConsumedOptions consumed_options; //new
    struct strSavedOptions saved_options; //new
    struct strPreferences option_preference;
    struct strPrices prices;
        
};


//Todo: Añadir estructuras de resultados para otros cálculos como strOptionsForBudgetResults y strOptionsForRangeOfBudgetsResults


//Typedefs

//////////////////////
//Codigo para pruebas
//
typedef void(*setPriceFunc_t)(int nProduct, double dAmount);
//Fin de código para pruebas
//////////////////////

//Estructuras para compartir entre C y C++

//Métodos para compartir entre C y C++
#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////
//Codigo para pruebas 
//void market_addPriceForProduct(int nProductId, double dPrice);
//void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount);

//Recibe un functor, al cual podremos llamar
//void market_setCallbackMethodForPrices(setPriceFunc_t setPriceFunc);

//long test_price_calculator_dll();

//int test_price_calculator_dll_with_str(struct strProductAmount2* strProdAmount);
//int calculate_prices_with_price_calculator(struct strScenarioInfo* strScenarioInfo);

//Fin de código para pruebas
/////////////////////////////

//////////////////////////////////////////////////////
//Métodos para manipular la estructura strScenarioInfo
void add_person_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, wchar_t wc_name[256], int size);
void add_product_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, wchar_t wc_name[256], int size);
void add_consumption_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, wchar_t wc_name[256], int size);
void add_saving_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, wchar_t wc_name[256], int size);
void add_owned_thing_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
void add_price_to_scenario_info(struct strScenarioInfo* pstrScenarioInfoInOut, wchar_t wc_product[256], int size, double dPrice);

void add_traded_thing_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
void add_consumed_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);
void add_saved_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_option[256], int size_option, double dAmount);

void clear_scenario_info_struct(struct strScenarioInfo* pstrScenarioInfoInOut);
struct strScenarioInfo createScenarioInfoStruct();
////////////////////////////////////////////////////////

//Calcula el ajuste de precios y devuelve el resultado en strScenarioInfo
int calculate_prices_with_price_calculator(struct strScenarioInfo* pstrScenarioInfoOutput);

//Métodos para cargar el escenario en BindToCpp, para después poder cargarlo en PriceCalculator
void add_person(wchar_t wc_person[256], int n_size);
void add_product(wchar_t wc_product[256], int n_size);
void add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
void add_saving_option(wchar_t wc_saving_option[256], int n_size);
void add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
void add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
void add_currency(wchar_t wc_currency[256], int n_size);
void add_preferences_for_person(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);

void ResetScenarioInfoGlobalCPPVariables();


#ifdef __cplusplus
}
#endif


