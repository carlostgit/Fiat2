// PriceCalculatorTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Includes para la librería estática
#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/Tester.h"
//

//includes para la librería dinámica DLL
//#include "../../PriceCalculatorDLL/PriceCalculatorDLL/PriceCalculatorDLL.h"
//

//include necesario para cargar librarías en ejecución "explicit linking"
#include "windows.h"
#include "libloaderapi.h"
//

#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"

#include <iostream>

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

int main()
{
    bool bTestSinDll = true;
    if (bTestSinDll)
    {

        std::cout << "Prueba de crear una escena sin usar la dll pero usando un puntero a CPriceCalculator!\n";
        pca::CPriceCalculator* pPriceCalculator = pca::CPriceCalculatorStaticUser::GetPriceCalculatorRef();
        LaunchPriceCalculatorDefaultTest(pPriceCalculator);
    }
    else
    {

        ////////////////////////////////////
        //Prueba linkando la librería dinámica en ejecución "explicit linking":
        std::cout << "Prueba de crear una escena linkando la libreria dinamica en ejecucion (explicit linking)!\n";

        //Si se usa una librería dinámica en GODOT, he comprobado q carga la librería solo si la pongo en el exe de godot
            std::wstring libraryName = L"PriceCalculatorDLL.dll";
            //HMODULE hDll = LoadLibrary(TEXT("PriceCalculatorDLL.dll"));
            HMODULE hDll = LoadLibrary(libraryName.c_str());
            if (!hDll || hDll == INVALID_HANDLE_VALUE) {
                std::wcout << "Unable to load library " << libraryName.c_str() << L" with 'explicit linking'!\n";
                std::cout << "Saliendo del programa por el fallo al cargar la libreria" << std::endl;
                return 0;
            }

            std::wcout << L"Library " << libraryName.c_str() << L" loaded\n";

            //typedef pca::CPriceCalculator* (*fpGetPriceCalculatorRefFromDLL2)();
            //extern "C" PRICECALCULATORDLL_API pca::CPriceCalculator * GetPriceCalculatorRefFromDLL2();

            std::string nombreMetodo = "GetPriceCalculatorRefFromDLL2";
            pca::CPriceCalculator*(*fpGetPriceCalculatorRefFromDLL2)();
            fpGetPriceCalculatorRefFromDLL2 = (pca::CPriceCalculator*(*)())(GetProcAddress(hDll, nombreMetodo.c_str()));

            if (fpGetPriceCalculatorRefFromDLL2)
            {

                std::wcout << "Hello World con la librería dinámica " << libraryName.c_str() << " linkada en ejecución!\n";
                std::cout << "Llamando al método: " << nombreMetodo << std::endl;                
                pca::CPriceCalculator* pPriceCalculator = fpGetPriceCalculatorRefFromDLL2();
                std::cout << "Dirección de memoria del objeto pPriceCalculator" << pPriceCalculator << std::endl;
                std::cout << "Ejecutando LaunchPriceCalculatorDefaultTest(pPriceCalculator);" << std::endl;
                LaunchPriceCalculatorDefaultTest(pPriceCalculator);
            }
            else
            {
                std::cout << "No se ha encontrado el metodo " << nombreMetodo;
                std::wcout << " en la libreria " << libraryName << std::endl;
            }

    }


    //////////////////////////////////
    //Prueba con la librería estática:
    //pca::CTester oTester;

    //oTester.Test_SatisfactionCurve();

    //oTester.Test_SatisfactionCalculator();

    //std::cout << "Hello world!" << std::endl;
    //return 0;

    //std::cout << "Hello World con la librería estática!\n";
    //std::cout << pca::CPriceCalculator::GetTestPrice() << std::endl;


    //////////////////////////////////
    //Prueba con la librería linkada en compilación:
    //std::cout << "Hello World con la librería dinámica cargada en compilacion!\n";
    //std::cout << GetTestPriceFromDLL() << std::endl;

    if (true)
    {
        //std::cout << "Prueba de crear una escena usando la dll!\n";
        //CreateEmptyMarketFromDLL();
        //CreateProductFromDLL("nut");
        //CreateProductFromDLL("chocolate");
        //CreateProductFromDLL("candy");
        //SetCurrencyFromDLL("nut");
        //AddToProduct_CreateConsumptionOptionFromDLL("nut", "nut_consumption");
        //AddToProduct_CreateConsumptionOptionFromDLL("chocolate", "chocolate_consumption");
        //AddToProduct_CreateConsumptionOptionFromDLL("candy", "candy_consumption");
        //AddToMarket_CreatePersonFromDLL("Peter");
        //AddToMarket_CreatePersonFromDLL("George");
        //AddToPerson_SetProductAmountFromDLL("Peter", "nut", 1.0);
        //AddToPerson_SetProductAmountFromDLL("Peter", "chocolate", 1.0);
        //AddToPerson_SetProductAmountFromDLL("Peter", "candy", 1.0);
        //AddToPerson_SetProductAmountFromDLL("George", "nut", 1.0);
        //AddToPerson_SetProductAmountFromDLL("George", "chocolate", 1.0);
        //AddToPerson_SetProductAmountFromDLL("George", "candy", 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("Peter", "nut_consumption", 1.0, 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("Peter", "chocolate_consumption", 1.0, 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("Peter", "candy_consumption", 1.0, 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("George", "nut_consumption", 1.0, 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("George", "chocolate_consumption", 1.0, 1.0);
        //AddToPerson_SetSatisfactionCurveForOptionFromDLL("George", "candy_consumption", 1.0, 1.0);

        //std::cout << "nut amount of Peter: " << GetProductAmountFromDLL("nut", "Peter") << std::endl;
        //std::cout << "chocolate amount of Peter: " << GetProductAmountFromDLL("chocolate", "Peter") << std::endl;
        //std::cout << "candy amount of Peter: " << GetProductAmountFromDLL("candy", "Peter") << std::endl;
        //std::cout << "nut amount of George: " << GetProductAmountFromDLL("nut", "George") << std::endl;
        //std::cout << "chcolate amount of George: " << GetProductAmountFromDLL("chocolate", "George") << std::endl;
        //std::cout << "candy amount of George: " << GetProductAmountFromDLL("candy", "George") << std::endl;
        //std::cout << "Get currency from DLL: " << GetCurrencyFromDLL() << std::endl;
        //std::cout << "Adusting prices from DLL: " << std::endl;
        //AdjustPricesFromDLL();
        ////GetPriceFromDLL("nut");
        ////GetPriceFromDLL("chocolate");
        ////GetPriceFromDLL("candy");

        //std::cout << "Price nut: " << GetPriceFromDLL("nut") << std::endl;
        //std::cout << "Price chocolate: " << GetPriceFromDLL("chocolate") << std::endl;
        //std::cout << "Price candy: " << GetPriceFromDLL("candy") << std::endl;

        ////std::cout << "IsProductFromDLL: " << IsProductFromDLL("productoprueba") << std::endl;



    ////////////////////////////////////
    ////Prueba linkando la librería dinámica en ejecución "explicit linking":

    ////Si se usa una librería dinámica en GODOT, he comprobado q carga la librería solo si la pongo en el exe de godot
    //    std::wstring libraryName = L"PriceCalculatorDLL.dll";
    //    //HMODULE hDll = LoadLibrary(TEXT("PriceCalculatorDLL.dll"));
    //    HMODULE hDll = LoadLibrary(libraryName.c_str());
    //    if (!hDll || hDll == INVALID_HANDLE_VALUE) {
    //        std::wcout << "Unable to load library " << libraryName.c_str() << L" with 'explicit linking'!\n";
    //        std::cout << "Saliendo del programa por el fallo al cargar la libreria" << std::endl;
    //        return 0;
    //    }

    //    std::wcout << L"Library " << libraryName.c_str() << L" loaded\n";

    //    std::string nombreMetodo = "GetTestPriceFromDLL";
    //    long(*functionPtr)();
    //    functionPtr = (long(*)())(GetProcAddress(hDll, nombreMetodo.c_str()));

    //    std::string nombreMetodo2 = "GetTestPriceFromDLL2";
    //    fpGetTestPriceFromDLL2 functionPtr2 = nullptr;
    //    functionPtr2 = (fpGetTestPriceFromDLL2)(GetProcAddress(hDll, nombreMetodo2.c_str()));


        //std::string nombreCreateEmptyMarket = "CreateEmptyMarketFromDLL";
        //fpCreateEmptyMarketFromDLL functionPtrCreateEmptyMarketFromDLL = nullptr;
        //functionPtrCreateEmptyMarketFromDLL = (fpCreateEmptyMarketFromDLL)(GetProcAddress(hDll, nombreCreateEmptyMarket.c_str()));


    //    if (functionPtr)
    //    {
    //        std::wcout << "Hello World con la librería dinámica " << libraryName.c_str() << " linkada en ejecución!\n";
    //        std::cout << "Llamando al método: " << nombreMetodo << std::endl;
    //        std::cout << functionPtr() << std::endl;
    //    }
    //    else
    //    {
    //        std::cout << "No se ha encontrado el metodo " << nombreMetodo;
    //        std::wcout << " en la libreria " << libraryName << std::endl;
    //    }

    //    if (functionPtr2)
    //    {
    //        std::cout << "Llamando al método: " << nombreMetodo2 << std::endl;
    //        std::cout << functionPtr2(10) << std::endl;
    //    }
    //    else
    //    {
    //        std::cout << "No se ha encontrado el metodo " << nombreMetodo2;
    //        std::wcout << " en la libreria " << libraryName << std::endl;
    //    }

    //    if (functionPtrCreateEmptyMarketFromDLL)
    //    {
    //        std::cout << "Llamando al método: " << nombreCreateEmptyMarket << std::endl;
    //        functionPtrCreateEmptyMarketFromDLL();
    //    }
    //    else
    //    {
    //        std::cout << "No se ha encontrado el metodo " << nombreCreateEmptyMarket;
    //        std::wcout << " en la libreria " << libraryName << std::endl;
    //    }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
