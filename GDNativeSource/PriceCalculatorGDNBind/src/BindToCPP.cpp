#include "BindToCPP.h"
#include "BindToCPP_CPPHeader.h"
#include "Defines.h"

#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"
#include "../../PriceCalculator/src/TradeCalculatorScenario.h"


//#include "windows.h"
//#include "libloaderapi.h"

#include <map>
#include <iostream>
#include <set>

//para transformar el wchar
#include <locale>
#include <codecvt>
#include <assert.h>


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

//extern "C" void market_addPriceForProduct(int nProductId, double dPrice)
//{
//    g_map_Product_Price[nProductId]=dPrice;
//}
//
//extern "C" void market_addOwnedAmountForPerson(int nPersonId, int nProductId, double dAmount)
//{
//    if(g_map_Person_mapProdAmount.end() == g_map_Person_mapProdAmount.find(nPersonId))
//    {
//
//        std::map<int,double> productAmount;
//        productAmount[nProductId]=dAmount;
//        g_map_Person_mapProdAmount[nPersonId] = productAmount;
//    }
//    else
//        g_map_Person_mapProdAmount[nPersonId][nProductId]=dAmount;
//}

extern "C" void market_setCallbackMethodForPrices(void(*setPrice)(int nProduct, double dAmount))
{
    m_setPrice = setPrice;

    //if (g_map_Product_Price.empty())
        m_setPrice(1,1.2);
    //else
    //{
    //    int nFirstAmount = g_map_Product_Price.begin()->first;
    //    int nSecondAmount = g_map_Product_Price.begin()->second;
    //    m_setPrice(nFirstAmount,nSecondAmount);

    //}
}

//extern "C" long test_price_calculator_dll()
//{
//    return 2;
//}

//Fin de pruebas
//////////////////////////////////////////////////////


extern "C" void LaunchPriceCalculatorDefaultTest(pca::CPriceCalculator* pPriceCalculator)
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

//extern "C" int test_price_calculator_dll_with_str(struct strProductAmount2* strProdAmount)
//{   
//    pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();
//
//    if (pPriceCalculator)
//    {
//        //LaunchPriceCalculatorDefaultTest(pPriceCalculator);
//        LaunchPriceCalculatorLoadedScenario(pPriceCalculator);
//
//        double dAmount = pPriceCalculator->GetProductAmount("nut", "Peter");
//
//        strProdAmount->dAmount = dAmount;
//    }
//
//    return (int)pPriceCalculator;
//
//    //strProdAmount->dAmount = 2.1;
//    //strProdAmount->nProductId = 3;
//
//    ////Si se usa una librería dinámica en GODOT, he comprobado q carga la librería solo si la pongo en el exe de godot
//    //std::wstring libraryName = L"PriceCalculatorDLL.dll";
//    ////HMODULE hDll = LoadLibrary(TEXT("PriceCalculatorDLL.dll"));
//    //HMODULE hDll = LoadLibrary(libraryName.c_str());
//    //if (!hDll || hDll == INVALID_HANDLE_VALUE) {
//    //    std::wcout << "Unable to load library " << libraryName.c_str() << L" with 'explicit linking'!\n";
//    //    std::cout << "Saliendo del programa por el fallo al cargar la libreria" << std::endl;
//    //    return 0;
//    //}
//
//    //std::wcout << L"Library " << libraryName.c_str() << L" loaded\n";
//
//    ////typedef pca::CPriceCalculator* (*fpGetPriceCalculatorRefFromDLL2)();
//    ////extern "C" PRICECALCULATORDLL_API pca::CPriceCalculator * GetPriceCalculatorRefFromDLL2();
//
//    //std::string nombreMetodo = "GetPriceCalculatorRefFromDLL2";
//    //pca::CPriceCalculator* (*fpGetPriceCalculatorRefFromDLL2)();
//    //fpGetPriceCalculatorRefFromDLL2 = (pca::CPriceCalculator * (*)())(GetProcAddress(hDll, nombreMetodo.c_str()));
//
//    //if (fpGetPriceCalculatorRefFromDLL2)
//    //{
//    //    std::wcout << "Hello World con la librería dinámica " << libraryName.c_str() << " linkada en ejecución!\n";
//    //    std::cout << "Llamando al método: " << nombreMetodo << std::endl;
//    //    pca::CPriceCalculator* pPriceCalculator = fpGetPriceCalculatorRefFromDLL2();
//    //    std::cout << "Dirección de memoria del objeto pPriceCalculator" << pPriceCalculator << std::endl;
//    //    std::cout << "Ejecutando LaunchPriceCalculatorDefaultTest(pPriceCalculator);" << std::endl;
//    //    LaunchPriceCalculatorDefaultTest(pPriceCalculator);
//
//    //    double dAmount = pPriceCalculator->GetProductAmount("nut", "Peter");
//
//    //    strProdAmount->dAmount = dAmount;
//
//    //    return (int)pPriceCalculator;
//    //}
//
//    return 0;
//}



/////////////////////////////////
//Adjust Price methods:


extern "C" int AP_adjust_price_with_price_calculator(struct strAdjustPriceResults* pstrAdjustPriceResultsOut)
{
    pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();

    if (pPriceCalculator)
    {
        oAdjustPrices.AdjustPriceWithPriceCalculator(pPriceCalculator, pstrAdjustPriceResultsOut);
    }
    else
    {
        return COD_ERROR_FALTA_OBJETO_PRICE_CALCULATOR;
    }

    return 0;

}

extern "C" void AP_add_person(wchar_t wc_person[256], int n_size)
{
    oAdjustPrices.AddPerson(wc_person, n_size);
}

extern "C" void AP_add_product(wchar_t wc_product[256], int n_size)
{    
    oAdjustPrices.AddProduct(wc_product, n_size);
}

extern "C" void AP_add_consumption_option(wchar_t wc_consumption_option[256], int n_size)
{
    oAdjustPrices.AddConsumptionOption(wc_consumption_option, n_size);
}

extern "C" void AP_add_saving_option(wchar_t wc_saving_option[256], int n_size)
{
    oAdjustPrices.AddSavingOption(wc_saving_option, n_size);
}

extern "C" void AP_add_person_owned(wchar_t wc_person[256], int n_size_person, wchar_t wc_product[256], int n_size_product, double dAmount)
{    
    oAdjustPrices.AddPersonOwned(wc_person, n_size_person, wc_product, n_size_product, dAmount);
}

void AP_add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product)
{
    oAdjustPrices.AddOptionProduct(wc_option, n_size_option, wc_product, n_size_product);
}

void AP_add_currency(wchar_t wc_currency[256], int n_size)
{
    oAdjustPrices.AddCurrency(wc_currency,n_size);
}

void AP_add_preferences_for_person(wchar_t wc_person[256], wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0)
{
    oAdjustPrices.AddPreferencesForPerson(wc_person, wc_option, d_maximum_satisfaction, d_preference_at_0);
}

void AP_reset_adjust_prices_data_input()
{
    oAdjustPrices.ResetAdjustPricesDataInput();
}

//End of Adjust prices methods:
/////////////////////////////////


/////////////////////////////////
//Adjust best combination methods:

//extern "C" int ABC_adjust_best_combination_with_price_calculator(struct strAdjustPriceResults* pstrAdjustPriceResultsOut)
//{
//    pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();
//
//    if (pPriceCalculator)
//    {
//        oAdjustBestCombination.AdjustBestCombinationWithPriceCalculator(pPriceCalculator, pstrAdjustPriceResultsOut);
//    }
//    else
//    {
//        return COD_ERROR_FALTA_OBJETO_PRICE_CALCULATOR;
//    }
//
//    return 0;
//
//}

extern "C" void ABC_add_budget(double dBudget)
{
    oAdjustBestCombination.AddBudget(dBudget);
}

extern "C" void ABC_add_product(wchar_t wc_product[256], int n_size)
{
    oAdjustBestCombination.AddProduct(wc_product, n_size);
}

extern "C" void ABC_add_consumption_option(wchar_t wc_consumption_option[256], int n_size)
{
    oAdjustBestCombination.AddConsumptionOption(wc_consumption_option, n_size);
}

extern "C" void ABC_add_saving_option(wchar_t wc_saving_option[256], int n_size)
{
    oAdjustBestCombination.AddSavingOption(wc_saving_option, n_size);
}

void ABC_add_option_product(wchar_t wc_option[256], int n_size_option, wchar_t wc_product[256], int n_size_product)
{
    oAdjustBestCombination.AddOptionProduct(wc_option, n_size_option, wc_product, n_size_product);
}

void ABC_add_product_price(wchar_t wc_product[256], int n_size_product, double dPrice)
{
    oAdjustBestCombination.AddProductPrice(wc_product, n_size_product, dPrice);
}

void ABC_add_currency(wchar_t wc_currency[256], int n_size)
{
    oAdjustBestCombination.AddCurrency(wc_currency, n_size);
}

void ABC_add_preferences(wchar_t wc_option[256], double d_maximum_satisfaction, double d_preference_at_0)
{
    oAdjustBestCombination.AddPreferences(wc_option, d_maximum_satisfaction, d_preference_at_0);
}

void ABC_reset_adjust_best_combination_data_input()
{
    oAdjustBestCombination.ResetAdjustBestCombinationDataInput();
}



extern "C" int ABC_adjust_best_combination_with_price_calculator(struct strAdjustBestCombinationResults* pstrAdjustBestCombinationResultsOut)
{
    //pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();

    pca::CTradeCalculatorScenario oTradeCalculatorScenario;

    /*oTradeCalculatorScenario.CreateEmptyMarket();
    oTradeCalculatorScenario.CreateEmptyReality();
    oTradeCalculatorScenario.CreateTradeCalculator();*/

    oAdjustBestCombination.AdjustBestCombinationWithPriceCalculator(&oTradeCalculatorScenario, pstrAdjustBestCombinationResultsOut);

    //if (pPriceCalculator)
    //{
    //    oAdjustBestCombination.AdjustBestCombinationWithPriceCalculator(pPriceCalculator, pstrAdjustBestCombinationResultsOut);
    //}
    //else
    //{
    //    return COD_ERROR_FALTA_OBJETO_PRICE_CALCULATOR;
    //}

    return 0;

}


//End of Adjust best combination methods:
/////////////////////////////////


