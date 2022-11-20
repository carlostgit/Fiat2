#include "../Market/market.h"

//#include <libloaderapi.h>
#include <Windows.h>
#include <tchar.h>
#include <libloaderapi.h>
#include <wchar.h>

#include <iostream>

using namespace std;

//tipo del método
//void DLL_EXPORT SomeFunction(const LPCSTR sometext);
//DWORD(*Arithmetic)(DWORD, DWORD);
//void(*SomeFunction)(const LPCSTR sometext);
typedef void(*SomeF)(const LPCSTR sometext);
//

int main()
{

    //SomeFunctionForStaticLibrary("Hello from statically linked lib");
    //SomeFunctionForStaticLibrary(3);

    //Ejemplo con load-time linking. Es necesario compilar linkando con la
    //librería estática
    cout << "Hello world!" << endl;
    //SomeFunction("Hello from load-time linked dll");
    //Fin del ejemplo con load-time linking.

    //Ejemplo con run-time inking. Creo que no es necesario compilar linkando
    //con la librería estática
    //HMODULE hDll = LoadLibrary(_T("Marketd.dll"));
    HMODULE hDll = LoadLibrary("Marketd.dll");
    if (!hDll || hDll == INVALID_HANDLE_VALUE) {
        cout << "unable to load libraray"<< std::endl;
        return 1;
    }

    cout << "Marketd.dll loaded"<< std::endl;

    void(*functionPtr)(const LPCSTR sometext);
    functionPtr = (SomeF)(GetProcAddress(hDll, "SomeFunction"));
    //Lo anterior queda más bonito, pero también se puede hacer
    //como en la siguiente linea, sin usar el typdef
    //functionPtr = (void(*)(const LPCSTR sometext))(GetProcAddress(hDll, "SomeFunction"));

    functionPtr("Hello from run-time linked dll");
    //Fin del ejemplo con run-time linking.

    return 0;
}
