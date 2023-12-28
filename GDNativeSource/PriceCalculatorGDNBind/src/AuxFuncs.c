#include "AuxFuncs.h"
#include "Defines.h"



//////////////////////////////////////////////////////////////
//Inicio de métodos para imprimir cosas en la consola de GODOT



void PrintInGodotConsole_Text_Size(wchar_t wchar_to_print[], size_t size)
{
    //Este método admite como máximo 256 caracteres    
    wchar_t wchar_to_print2[MAXSTRING];
    for (int i = 0;i < MAXSTRING;i++)
    {
        wchar_to_print2[i] = wchar_to_print[i];
    }

    //int result = MessageBox(NULL, wchar_to_print, L"Message", MB_OK);
    godot_int godint_to_print_length = wcslen(wchar_to_print2);

    //wchar_t wchar_for_number_to_print[30];
    //swprintf(wchar_for_number_to_print, sizeof(wchar_for_number_to_print) / sizeof(wchar_for_number_to_print[0]), L"%d", godint_to_print_length);
    //MessageBox(NULL, wchar_for_number_to_print, L"Message", MB_OK);
    godot_string godstring_to_print;
    api_godot_core->godot_string_new_with_wide_string(&godstring_to_print, &wchar_to_print2, godint_to_print_length);

    //MessageBox(NULL, wchar_to_print2, L"Message", MB_OK);
    //MessageBox(NULL, api->godot_string_wide_str(&godstring_to_print), L"Message", MB_OK);

    api_godot_core->godot_print(&godstring_to_print);
}

void PrintInGodotConsole_Text(wchar_t wchar_to_print[])
{
    PrintInGodotConsole_Text_Size(wchar_to_print, MAXSTRING);
}

void PrintInGodotConsole_Int(int intNumber)
{
    wchar_t wchar_to_print[MAXSTRING]; // Choose a buffer size that is large enough to hold your integer as a wide string
    swprintf(wchar_to_print, sizeof(wchar_to_print) / sizeof(wchar_to_print[0]), L"%d", intNumber);
    int numberOfCharacters = wcslen(wchar_to_print);
    PrintInGodotConsole_Text_Size(wchar_to_print, numberOfCharacters);
}

void PrintInGodotConsole_Double(double doubleNumber)
{
    wchar_t wchar_to_print[MAXSTRING]; // Choose a buffer size that is large enough to hold your integer as a wide string
    swprintf(wchar_to_print, sizeof(wchar_to_print) / sizeof(wchar_to_print[0]), L"%f", doubleNumber);
    int numberOfCharacters = wcslen(wchar_to_print);
    PrintInGodotConsole_Text_Size(wchar_to_print, numberOfCharacters);
}

//Fin de métodos para imprimir cosas en la consola de GODOT
//////////////////////////////////////////////////////////////

