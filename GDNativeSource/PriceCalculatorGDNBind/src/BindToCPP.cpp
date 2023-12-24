#include "BindToCPP.h"
#include "BindToCPP_CPPHeader.h"

#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"

//#include "../VSProject/PriceCalculatorGDNBind/Prueba.h"
//#include "../VSProject/PriceCalculatorGDNBind/Prueba2.h"

//#include "windows.h"
//#include "libloaderapi.h"

#include <map>
#include <iostream>
#include <set>

//para transformar el wchar
#include <locale>
#include <codecvt>

std::map<int,double> g_map_Product_Price;
std::map<int,std::map<int,double> > g_map_Person_mapProdAmount;


void add_person_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size)
{ 
    wchar_t* pwc_name_in_struct = pstrScenarioInfo->name_persons[pstrScenarioInfo->n_num_of_persons].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->n_num_of_persons += 1;
}

void add_person_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sPerson)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_person_name = converter.from_bytes(sPerson);

    wchar_t array_wc_not_const[256];
    int size = ws_person_name.size();
    wcsncpy(array_wc_not_const, ws_person_name.c_str(), size);

    add_person_to_scenario_info(pstrScenarioInfo, array_wc_not_const, size);
}

void add_product_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrScenarioInfo->name_products[pstrScenarioInfo->n_num_of_products].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->n_num_of_products += 1;
}

void add_product_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_not_const[256];
    int size = ws_product_name.size();
    wcsncpy(array_wc_not_const, ws_product_name.c_str(), size);

    add_product_to_scenario_info(pstrScenarioInfo, array_wc_not_const, size);
}

void add_consumption_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrScenarioInfo->name_consumption_options[pstrScenarioInfo->n_num_of_consumption_options].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->n_num_of_consumption_options += 1;
}

void add_consumption_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_not_const[256];
    int size = ws_option_name.size();
    wcsncpy(array_wc_not_const, ws_option_name.c_str(), size);

    add_consumption_option_to_scenario_info(pstrScenarioInfo, array_wc_not_const, size);
}

void add_saving_option_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_name[256], int size)
{
    wchar_t* pwc_name_in_struct = pstrScenarioInfo->name_saving_options[pstrScenarioInfo->n_num_of_saving_options].wc_name;
    wcsncpy(pwc_name_in_struct, wc_name, size);
    //pwc_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->n_num_of_saving_options += 1;
}

void add_saving_option_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sOption)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_option_name = converter.from_bytes(sOption);

    wchar_t array_wc_not_const[256];
    int size = ws_option_name.size();
    wcsncpy(array_wc_not_const, ws_option_name.c_str(), size);

    add_saving_option_to_scenario_info(pstrScenarioInfo, array_wc_not_const, size);
}

void add_owned_thing_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, int person_index, wchar_t wc_person[256], int size_person, wchar_t wc_product[256], int size_product, double dAmount)
{
    //int person_index = pstrScenarioInfo->owned_things.n_num_persons;
    int prod_amount_index = pstrScenarioInfo->owned_things.person_prod_amounts[person_index].n_num_prod_amounts;

    wchar_t* pwc_person_name_in_struct = pstrScenarioInfo->owned_things.person_prod_amounts[person_index].name_person.wc_name;
    wchar_t* pwc_product_name_in_struct = pstrScenarioInfo->owned_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].name_product.wc_name;
    
    wcsncpy(pwc_person_name_in_struct, wc_person, size_person);
    //pwc_person_name_in_struct[size_person - 1] = L'\0';  // Ensure null-termination

    wcsncpy(pwc_product_name_in_struct, wc_product, size_product);
    //pwc_product_name_in_struct[size_product - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->owned_things.person_prod_amounts[person_index].prod_amounts[prod_amount_index].dAmount = dAmount;
    
    if (pstrScenarioInfo->owned_things.n_num_persons < person_index + 1)
    {
        pstrScenarioInfo->owned_things.n_num_persons = person_index + 1;
    }

    pstrScenarioInfo->owned_things.person_prod_amounts[person_index].n_num_prod_amounts += 1;
}

void add_owned_thing_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, int person_index, std::string sPerson, std::string sProduct, double dAmount)
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

    add_owned_thing_to_scenario_info(pstrScenarioInfo, person_index, array_wc_person_not_const, size_person, array_wc_product_not_const, size_product, dAmount);
}

void add_price_to_scenario_info(struct strScenarioInfo* pstrScenarioInfo, wchar_t wc_product[256], int size, double dPrice)
{    
    int prod_price_index = pstrScenarioInfo->prices.n_num_prices;
    
    wchar_t* pwc_product_name_in_struct = pstrScenarioInfo->prices.prod_price[prod_price_index].name_product.wc_name;
    
    wcsncpy(pwc_product_name_in_struct, wc_product, size);
    //pwc_product_name_in_struct[size - 1] = L'\0';  // Ensure null-termination

    pstrScenarioInfo->prices.prod_price[prod_price_index].dAmount = dPrice;

    pstrScenarioInfo->prices.n_num_prices += 1;    
}

void add_price_to_scenario_info_cpp(struct strScenarioInfo* pstrScenarioInfo, std::string sProduct, double dPrice)
{
    // Convert narrow string to wide string
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring ws_product_name = converter.from_bytes(sProduct);

    wchar_t array_wc_not_const[256];
    int size = ws_product_name.size();
    wcsncpy(array_wc_not_const, ws_product_name.c_str(), size);

    add_price_to_scenario_info(pstrScenarioInfo, array_wc_not_const, size, dPrice);

}

void clear_scenario_info(struct strScenarioInfo* pstrScenarioInfo)
{
    memset(pstrScenarioInfo, 0, sizeof(strScenarioInfo));
}

//////////////////////////////////////////////////////
//Prueba

void(*m_setPrice)(int nProduct, double dAmount)=0;

//extern "C" double market_calculationTest(int i)
//{
//    double dI = static_cast<double>(i);
//    dI += pca::CPriceCalculator::GetTestPrice();
//
//    return dI;
//}

extern "C" void market_addPriceForProduct(int nProductId, double dPrice)
{
    g_map_Product_Price[nProductId]=dPrice;
}

extern "C" void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount)
{
    if(g_map_Person_mapProdAmount.end() == g_map_Person_mapProdAmount.find(nPersonId))
    {

        std::map<int,double> productAmount;
        productAmount[nProductId]=dAmount;
        g_map_Person_mapProdAmount[nPersonId] = productAmount;
    }
    else
        g_map_Person_mapProdAmount[nPersonId][nProductId]=dAmount;
}

extern "C" void market_setCallbackMethodForPrices(void(*setPrice)(int nProduct, double dAmount))
{
    m_setPrice = setPrice;

    if (g_map_Product_Price.empty())
        m_setPrice(1,1.2);
    else
    {
        int nFirstAmount = g_map_Product_Price.begin()->first;
        int nSecondAmount = g_map_Product_Price.begin()->second;
        m_setPrice(nFirstAmount,nSecondAmount);

    }
}

extern "C" long test_price_calculator_dll()
{
    return 2;
}

//Fin de pruebas
//////////////////////////////////////////////////////

void LoadPriceCalculationResults(pca::CPriceCalculator* pPriceCalculator, struct strScenarioInfo* pstrScenarioInfo)
{
    int index = 0;

    for (auto& person : g_setPersons)
    {
        add_person_to_scenario_info_cpp(pstrScenarioInfo, person);
    }

    for (auto& product : g_setProducts)
    {
        double dPrice = pPriceCalculator->GetPrice(product);
        add_price_to_scenario_info_cpp(pstrScenarioInfo, product, dPrice);
    }

    for (auto& consumption_option : g_setConsumptionOptions)
    {
        add_consumption_option_to_scenario_info_cpp(pstrScenarioInfo, consumption_option);
    }

    for (auto& saving_option : g_setSavingOptions)
    {
        add_saving_option_to_scenario_info_cpp(pstrScenarioInfo, saving_option);
    }

    int person_index = 0;
    for (auto& person : g_setPersons)
    {
        for (auto& product : g_setProducts)
        {
            double dAmount = pPriceCalculator->GetProductAmount(product, person);
            add_owned_thing_to_scenario_info_cpp(pstrScenarioInfo, person_index, person, product, dAmount);
        }    
        person_index++;
    }

        
        
    



    //TODO. Seguir aqu�. Pero cambiar lo anterior, para hacerlo menos complicado
    //Igual tengo que cambiar los m�todos de la estructura, para que sean enteramente en c++
    //aceptando std:string. El constructor de la estructura es el �nico que tiene que ser en c
    //std::set<std::string> g_setPersons;
    //std::set<std::string> g_setProducts;
    //std::set<std::string> g_setConsumptionOptions;
    //std::set<std::string> g_setSavingOptions;
    //std::map<std::string, std::map<std::string, double> > g_mapPerson_ProdAmount;
    //std::map<std::string, std::string> g_mapOptionProduct;
    //std::string g_sCurrency;

}

void LaunchPriceCalculatorLoadedScenario(pca::CPriceCalculator* pPriceCalculator)
{
    pPriceCalculator->CreateEmptyReality();
    for (auto& product : g_setProducts)
    {
        pPriceCalculator->CreateProduct(product);
    }

    for (auto& pairOptionProduct : g_mapOptionProduct)
    {
        pPriceCalculator->AddToProduct_CreateConsumptionOption(pairOptionProduct.second, pairOptionProduct.first);
    }

    pPriceCalculator->CreateEmptyMarket();
   
    pPriceCalculator->SetCurrency(g_sCurrency);

    for (auto& person : g_setPersons)
    {
        pPriceCalculator->AddToMarket_CreatePerson(person);
    }

    for (auto& pairperson_prodamounts : g_mapPerson_ProdAmount)
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

    for (auto& person : g_setPersons)
    {        
        std::set<std::string> setOptions = g_setConsumptionOptions;
        setOptions.insert(g_setSavingOptions.begin(), g_setSavingOptions.end());

        for (auto& option : setOptions)
        {
            //TODO: a�adir la configuraci�n de esto
            double dValueAt0 = 1;
            double dMaxValue = 10;

            pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption(person, option, dValueAt0, dMaxValue);
        }
    }

    pPriceCalculator->AdjustPrices();

}


void LaunchPriceCalculatorDefaultTest(pca::CPriceCalculator* pPriceCalculator)
{
    pPriceCalculator->CreateEmptyReality();
    pPriceCalculator->CreateProduct("nut");
    pPriceCalculator->CreateProduct("chocolate");
    pPriceCalculator->CreateProduct("candy");

    pPriceCalculator->AddToProduct_CreateConsumptionOption("nut", "nut_consumption");
    pPriceCalculator->AddToProduct_CreateConsumptionOption("chocolate", "chocolate_consumption");
    pPriceCalculator->AddToProduct_CreateConsumptionOption("candy", "candy_consumption");
    pPriceCalculator->CreateEmptyMarket();
    pPriceCalculator->SetCurrency("nut");
    pPriceCalculator->AddToMarket_CreatePerson("Peter");
    pPriceCalculator->AddToMarket_CreatePerson("George");
    pPriceCalculator->AddToPerson_SetProductAmount("Peter", "nut", 1.0);
    pPriceCalculator->AddToPerson_SetProductAmount("Peter", "chocolate", 1.0);
    pPriceCalculator->AddToPerson_SetProductAmount("Peter", "candy", 1.0);
    pPriceCalculator->AddToPerson_SetProductAmount("George", "nut", 1.0);
    pPriceCalculator->AddToPerson_SetProductAmount("George", "chocolate", 1.0);
    pPriceCalculator->AddToPerson_SetProductAmount("George", "candy", 1.0);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("Peter", "nut_consumption", 1.0, 1.0);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("Peter", "chocolate_consumption", 1.1, 1.1);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("Peter", "candy_consumption", 2.2, 2.2);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("George", "nut_consumption", 1.0, 1.0);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("George", "chocolate_consumption", 10.5, 10.5);
    pPriceCalculator->AddToPerson_SetSatisfactionCurveForOption("George", "candy_consumption", 40.6, 40.6);


    std::cout << "Amount nut Peter: " << pPriceCalculator->GetProductAmount("nut", "Peter") << std::endl;
    std::cout << "Amount chocolate Peter: " << pPriceCalculator->GetProductAmount("chocolate", "Peter") << std::endl;
    std::cout << "Amount candy Peter: " << pPriceCalculator->GetProductAmount("candy", "Peter") << std::endl;
    std::cout << "Amount nut George: " << pPriceCalculator->GetProductAmount("nut", "George") << std::endl;
    std::cout << "Amount chocolate George: " << pPriceCalculator->GetProductAmount("chocolate", "George") << std::endl;
    std::cout << "Amount candy George: " << pPriceCalculator->GetProductAmount("candy", "George") << std::endl;

    std::cout << "Amount nut_consumption Peter: " << pPriceCalculator->GetOptionAmount("nut_consumption", "Peter") << std::endl;
    std::cout << "Amount chocolate_consumption Peter: " << pPriceCalculator->GetOptionAmount("chocolate_consumption", "Peter") << std::endl;
    std::cout << "Amount candy_consumption Peter: " << pPriceCalculator->GetOptionAmount("candy_consumption", "Peter") << std::endl;
    std::cout << "Amount nut_consumption George: " << pPriceCalculator->GetOptionAmount("nut_consumption", "George") << std::endl;
    std::cout << "Amount chocolate_consumption George: " << pPriceCalculator->GetOptionAmount("chocolate_consumption", "George") << std::endl;
    std::cout << "Amount candy_consumption George: " << pPriceCalculator->GetOptionAmount("candy_consumption", "George") << std::endl;

    std::cout << "Desired nut amount of Peter: " << pPriceCalculator->GetDesiredProdAmount("Peter", "nut") << std::endl;
    std::cout << "Desired chocolate amount of Peter: " << pPriceCalculator->GetDesiredProdAmount("Peter", "chocolate") << std::endl;
    std::cout << "Desired candy amount of Peter: " << pPriceCalculator->GetDesiredProdAmount("Peter", "candy") << std::endl;
    std::cout << "Desired nut amount of George: " << pPriceCalculator->GetDesiredProdAmount("George", "nut") << std::endl;
    std::cout << "Desired chocolate amount of George: " << pPriceCalculator->GetDesiredProdAmount("George", "chocolate") << std::endl;
    std::cout << "Desired candy amount of George: " << pPriceCalculator->GetDesiredProdAmount("George", "candy") << std::endl;


    pPriceCalculator->AdjustPrices();

    std::cout << "Price nut: " << pPriceCalculator->GetPrice("nut") << std::endl;
    std::cout << "Price chocolate: " << pPriceCalculator->GetPrice("chocolate") << std::endl;
    std::cout << "Price candy: " << pPriceCalculator->GetPrice("candy") << std::endl;

    std::cout << "Amount nut Peter: " << pPriceCalculator->GetProductAmount("nut", "Peter") << std::endl;
    std::cout << "Amount chocolate Peter: " << pPriceCalculator->GetProductAmount("chocolate", "Peter") << std::endl;
    std::cout << "Amount candy Peter: " << pPriceCalculator->GetProductAmount("candy", "Peter") << std::endl;
    std::cout << "Amount nut George: " << pPriceCalculator->GetProductAmount("nut", "George") << std::endl;
    std::cout << "Amount chocolate George: " << pPriceCalculator->GetProductAmount("chocolate", "George") << std::endl;
    std::cout << "Amount candy George: " << pPriceCalculator->GetProductAmount("candy", "George") << std::endl;

    pPriceCalculator->PrintPersonOptionAdjustmentToFile("Peter");
    pPriceCalculator->PrintPersonsOptionAdjustmentToFile();

}

extern "C" int test_price_calculator_dll_with_str(struct strProductAmount2* strProdAmount)
{   
    pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();

    if (pPriceCalculator)
    {
        //LaunchPriceCalculatorDefaultTest(pPriceCalculator);
        LaunchPriceCalculatorLoadedScenario(pPriceCalculator);

        double dAmount = pPriceCalculator->GetProductAmount("nut", "Peter");

        strProdAmount->dAmount = dAmount;
    }

    return (int)pPriceCalculator;

    //strProdAmount->dAmount = 2.1;
    //strProdAmount->nProductId = 3;

    ////Si se usa una librer�a din�mica en GODOT, he comprobado q carga la librer�a solo si la pongo en el exe de godot
    //std::wstring libraryName = L"PriceCalculatorDLL.dll";
    ////HMODULE hDll = LoadLibrary(TEXT("PriceCalculatorDLL.dll"));
    //HMODULE hDll = LoadLibrary(libraryName.c_str());
    //if (!hDll || hDll == INVALID_HANDLE_VALUE) {
    //    std::wcout << "Unable to load library " << libraryName.c_str() << L" with 'explicit linking'!\n";
    //    std::cout << "Saliendo del programa por el fallo al cargar la libreria" << std::endl;
    //    return 0;
    //}

    //std::wcout << L"Library " << libraryName.c_str() << L" loaded\n";

    ////typedef pca::CPriceCalculator* (*fpGetPriceCalculatorRefFromDLL2)();
    ////extern "C" PRICECALCULATORDLL_API pca::CPriceCalculator * GetPriceCalculatorRefFromDLL2();

    //std::string nombreMetodo = "GetPriceCalculatorRefFromDLL2";
    //pca::CPriceCalculator* (*fpGetPriceCalculatorRefFromDLL2)();
    //fpGetPriceCalculatorRefFromDLL2 = (pca::CPriceCalculator * (*)())(GetProcAddress(hDll, nombreMetodo.c_str()));

    //if (fpGetPriceCalculatorRefFromDLL2)
    //{
    //    std::wcout << "Hello World con la librer�a din�mica " << libraryName.c_str() << " linkada en ejecuci�n!\n";
    //    std::cout << "Llamando al m�todo: " << nombreMetodo << std::endl;
    //    pca::CPriceCalculator* pPriceCalculator = fpGetPriceCalculatorRefFromDLL2();
    //    std::cout << "Direcci�n de memoria del objeto pPriceCalculator" << pPriceCalculator << std::endl;
    //    std::cout << "Ejecutando LaunchPriceCalculatorDefaultTest(pPriceCalculator);" << std::endl;
    //    LaunchPriceCalculatorDefaultTest(pPriceCalculator);

    //    double dAmount = pPriceCalculator->GetProductAmount("nut", "Peter");

    //    strProdAmount->dAmount = dAmount;

    //    return (int)pPriceCalculator;
    //}

    return 0;
}

//extern "C" int calculate_prices_with_price_calculator(struct strScenarioInfo* pstrScenarioInfo)
extern "C" int calculate_prices_with_price_calculator(struct strScenarioInfo* pstrScenarioInfo)
{
    pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();

    if (pPriceCalculator)
    {
        //LaunchPriceCalculatorDefaultTest(pPriceCalculator);
        LaunchPriceCalculatorLoadedScenario(pPriceCalculator);

        //TODO. Devolver aqu� resultados a GODOT, por el argumento pstrScenarioInfo
        //o de alguna otra manera mejor
        double dAmount = pPriceCalculator->GetProductAmount("nut", "Peter");

        pPriceCalculator->PrintPricesEvolution();
        pPriceCalculator->PrintPersonsOptionAdjustmentToFile();

        LoadPriceCalculationResults(pPriceCalculator, pstrScenarioInfo);
        
    }

    return (int)pPriceCalculator;

}

extern "C" void add_person(wchar_t wc_person[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_person);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sPerson = converter.to_bytes(wide_str);

    g_setPersons.insert(sPerson);
}

extern "C" void add_product(wchar_t wc_product[256], int n_size)
{    
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_product);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sProduct = converter.to_bytes(wide_str);

    g_setProducts.insert(sProduct);
}

extern "C" void add_consumption_option(wchar_t wc_consumption_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_consumption_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sConsumptionOption = converter.to_bytes(wide_str);

    g_setConsumptionOptions.insert(sConsumptionOption);
}

extern "C" void add_saving_option(wchar_t wc_saving_option[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str(wc_saving_option);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sSavingOption = converter.to_bytes(wide_str);

    g_setSavingOptions.insert(sSavingOption);
}

extern "C" void add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount)
{    
    std::map<std::string,double> mapProdAmount;

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sProduct = converter.to_bytes(wc_product);

    mapProdAmount[sProduct] = dAmount;        
    std::string sPerson = converter.to_bytes(wc_person);

    if(g_mapPerson_ProdAmount.end() == g_mapPerson_ProdAmount.find(sPerson))
        g_mapPerson_ProdAmount[sPerson] = mapProdAmount;
    else
    {
        g_mapPerson_ProdAmount[sPerson][sProduct] = dAmount;
    }
}

void add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product)
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

void add_currency(wchar_t wc_currency[256], int n_size)
{
    // Convert wchar_t array to std::wstring
    std::wstring wide_str_currency(wc_currency);

    // Convert std::wstring to std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string sCurrency = converter.to_bytes(wide_str_currency);

    g_sCurrency = sCurrency;
}