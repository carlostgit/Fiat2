
struct strProductAmount2
{
    int nProductId;
    double dAmount;
};

struct strName
{
    wchar_t wc_name[256];
    //wchar_t wc_name[256];
};

//// Define the innermost structure
//struct InnerStruct {
//    int innerData;
//    struct strName names[3];
//    // You can add more fields as needed
//};
//
//// Define the middle structure containing an array of InnerStruct
//struct MiddleStruct {
//    int middleData;
//    struct InnerStruct innerArray[3]; // Example array size: 3
//    struct strName name_persons[25];
//    // You can add more fields as needed
//};



struct strProductAmount
{
    struct strName name_product;
    double dAmount;
};

struct strOwnedThings
{
    int n_num_persons;
    struct strName name_persons[25];
    
    struct strProductAmount prod_amounts[25];
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

    struct strName name_persons[25];
    int n_num_of_persons;
    struct strName name_products[25];
    int n_num_of_products;
    struct strName name_consumptions[25];
    int n_num_of_consumption_options;
    struct strName names_saving[25];
    int n_num_of_saving_options;
    struct strOwnedThings owned_things[25];
    //struct MiddleStruct middleArray[25];
};



//Typedefs
typedef void(*setPriceFunc_t)(int nProduct, double dAmount);

//Estructuras para compartir entre C y C++


//Métodos para compartir entre C y C++
#ifdef __cplusplus
extern "C" {
#endif



//double market_calculationTest(int i);

void market_addPriceForProduct(int nProductId, double dPrice);
void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount);

//Recibe un functor, al cual podremos llamar
void market_setCallbackMethodForPrices(setPriceFunc_t setPriceFunc);

long test_price_calculator_dll();

int test_price_calculator_dll_with_str(struct strProductAmount2* strProdAmount);
//int calculate_prices_with_price_calculator(struct strScenarioInfo* strScenarioInfo);
int calculate_prices_with_price_calculator(struct strScenarioInfo* pstrProdAmount);

void add_person(wchar_t wc_person[256], int n_size);
void add_product(wchar_t wc_product[256], int n_size);
void add_consumption_option(wchar_t wc_consumption_option[256], int n_size);
void add_saving_option(wchar_t wc_saving_option[256], int n_size);
void add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount);
void add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product);


#ifdef __cplusplus
}
#endif


