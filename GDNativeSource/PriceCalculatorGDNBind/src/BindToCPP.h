
struct strProductAmount2
{
    int nProductId;
    double dAmount;    
};

struct strName
{
    wchar_t wc_name[256];
};

struct strProductAmount
{
    struct strName name_product;
    double dAmount;
};

struct strPersonProductAmounts
{
    struct strName name_person;
    int n_num_prod_amounts;
    struct strProductAmount prod_amounts[25];
};

struct strOwnedThings
{
    int n_num_persons;
    struct strPersonProductAmounts person_prod_amounts[25];    
};

struct strPrices
{
    int n_num_prices;
    struct strProductAmount prod_price[25];
};

struct strScenarioInfo
{
    //struct strName name_persons[256];
    //int n_num_of_persons;
    //struct strName name_products[256];
    //int n_num_of_products;
    //struct strName name_consumptions[256];
    //int n_num_of_consumption_options;
    //struct strName names_saving[256];
    //int n_num_of_saving_options;
    //struct strOwnedThings owned_things[256];
    //Con lo de arriba obtengo un stack overflow

    struct strName name_persons[25];
    int n_num_of_persons;
    struct strName name_products[25];
    int n_num_of_products;
    struct strName name_consumption_options[25];
    int n_num_of_consumption_options;
    struct strName name_saving_options[25];
    int n_num_of_saving_options;
    struct strOwnedThings owned_things;
    struct strPrices prices;
        
};

//M�todos para manipular la estructura:
struct strScenarioInfo createScenarioInfoStruct() {
    struct strScenarioInfo newStruct = { 0 };
    return newStruct;
}


//Fin de m�todos para manipular la estructura

//Typedefs

//////////////////////
//Codigo para pruebas
//
typedef void(*setPriceFunc_t)(int nProduct, double dAmount);
//Fin de c�digo para pruebas
//////////////////////

//Estructuras para compartir entre C y C++

//M�todos para compartir entre C y C++
#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////
//Codigo para pruebas 
void market_addPriceForProduct(int nProductId, double dPrice);
void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount);

//Recibe un functor, al cual podremos llamar
void market_setCallbackMethodForPrices(setPriceFunc_t setPriceFunc);

long test_price_calculator_dll();

int test_price_calculator_dll_with_str(struct strProductAmount2* strProdAmount);
//int calculate_prices_with_price_calculator(struct strScenarioInfo* strScenarioInfo);

//Fin de c�digo para pruebas
/////////////////////////////

//////////////////////////////////////////////////////
//M�todos para manipular la estructura strScenarioInfo
void add_person_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size);
void add_product_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size);
void add_consumption_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size);
void add_saving_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size);
void add_owned_thing_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount);
void add_price_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_product[256], int size, double dPrice);
void clear_scenario_info(struct strScenarioInfo* pstrScenarioInfo);
////////////////////////////////////////////////////////

int calculate_prices_with_price_calculator(struct strScenarioInfo* pstrProdAmount);

void add_person(wchar_t wc_person[256], int n_size);
void add_product(wchar_t wc_product[256], int n_size);
void add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
void add_saving_option(wchar_t wc_saving_option[256], int n_size);
void add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
void add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);
void add_currency(wchar_t wc_currency[256], int n_size);

#ifdef __cplusplus
}
#endif


