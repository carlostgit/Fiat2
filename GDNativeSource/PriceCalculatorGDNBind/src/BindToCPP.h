
struct strProductAmount
{
    int nProductId;
    double dAmount;
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

void test_price_calculator_dll_with_str(struct strProductAmount* strProdAmount);

#ifdef __cplusplus
}
#endif


