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


struct strAdjustPriceResults //TODO: Cambiar el nombre a esto a a algo así como strAdjustPriceResults
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


//Estructuras para los resultados de AdjustBestCombinationResults
struct strOptionAmounts
{
    struct strName name_person;
    int n_num_option_amounts;
    struct strOptionAmount option_amounts[25];
};

struct strAdjustBestCombinationResults 
{    
    
    struct strOptionAmounts adjusted_options;  
};
//


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
//int adjust_price_with_price_calculator(struct strAdjustPriceResults* strAdjustPriceResults);

//Fin de código para pruebas
/////////////////////////////

//////////////////////////
///Adjust Prices methods:

//Calcula el ajuste de precios y devuelve el resultado en strAdjustPriceResults
int AP_adjust_price_with_price_calculator(struct strAdjustPriceResults* pstrAdjustPriceResultsOutput);

//Métodos para cargar el escenario de ajuste de precios en AdjustPrices, para después poder cargarlo en PriceCalculator
void AP_add_person(wchar_t wc_person[256], int n_size);
void AP_add_product(wchar_t wc_product[256], int n_size);
void AP_add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
void AP_add_saving_option(wchar_t wc_saving_option[256], int n_size);
void AP_add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
void AP_add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
void AP_add_currency(wchar_t wc_currency[256], int n_size);
void AP_add_preferences_for_person(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);

void AP_reset_adjust_prices_data_input();
//
//////////////////////////

//////////////////////////
///Adjust Best Combination methods:

//TODO:
//int ABC_adjust_best_combination_with_price_calculator(struct strAdjustBestCombinationResults* pstrAdjustPriceResultsOutput);

void ABC_add_budget(double dBudget);
void ABC_add_product(wchar_t wc_product[256], int n_size);
void ABC_add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
void ABC_add_saving_option(wchar_t wc_saving_option[256], int n_size);

void ABC_add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
void ABC_add_currency(wchar_t wc_currency[256], int n_size);
void ABC_add_preferences(wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0);

void ABC_reset_adjust_best_combination_data_input();

int ABC_adjust_best_combination_with_price_calculator(struct strAdjustBestCombinationResults* pstrAdjustPriceResultsOutput);
//
//////////////////////////



#ifdef __cplusplus
}
#endif


