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

///////////////////////////////////////////////////////
//Inicio de los métodos para leer diccionarios de godot

godot_variant GetGovarFromAFName(struct strAFName* pName, const godot_gdnative_core_api_struct* api_arg)
{
    godot_variant retpGovar;

    wchar_t* pwchar_product_name = pName->wc_name;
    int size = wcslen(pwchar_product_name);
    int size_with_null = size + 1;
    godot_string godstring_product_name;
    api_arg->godot_string_new_with_wide_string(&godstring_product_name, pwchar_product_name, size_with_null);
    godot_variant godvar_product_name;
    api_arg->godot_variant_new_string(&godvar_product_name, &godstring_product_name);

    retpGovar = godvar_product_name;

    return retpGovar;
}

struct strAFName GetAFNameFromGovar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg)
{
    struct strAFName retName;

    godot_string godstring_name = api_arg->godot_variant_as_string(&govar_name_arg);

    const wchar_t* pwc_name = api_arg->godot_string_wide_str(&godstring_name);
    //wchar_t array_wc_not_const[256];
    //int size = (*pwc_key).size();    
    int size = wcslen(pwc_name);
    int size_with_null = size + 1;
    //for (int i = 0;i < 256;i++)
    //    retName.wc_name[i] = pwc_name[i];
    
    //wcsncpy(array_wc_not_const, pwc_name, size);
    wcsncpy(retName.wc_name, pwc_name, size_with_null);


    ////struct strAFName strName;
    //int j = 0;
    //for (j = 0;j < 256;j++)
    //{
    //    //strName.wc_name[j] = array_wc_not_const;
    //    retName.wc_name[j] = array_wc_not_const[j];
    //}    

    return retName;
}

struct strAFNames GetAFNamesFromGovar(godot_variant govar_name_arg, const godot_gdnative_core_api_struct* api_arg)
{
    struct strAFNames retNames;

    godot_string godstring_name = api_arg->godot_variant_as_string(&govar_name_arg);
    godot_array godarray_names = api_arg->godot_variant_as_array(&govar_name_arg);

    godot_int godint_size_of_names = api_arg->godot_array_size(&godarray_names);

    printf("Size of array: %d \n", godint_size_of_names);

    int i = 0;
    for (i = 0;i < godint_size_of_names;i++)
    {
        godot_variant godvar_name;
        godvar_name = api_arg->godot_array_get(&godarray_names, i);
        godot_string godstring_name = api_arg->godot_variant_as_string(&godvar_name);

        const wchar_t* pwc_name = api_arg->godot_string_wide_str(&godstring_name);
        //wchar_t array_wc_not_const[256];
        //int size = (*pwc_key).size();    
        int size = wcslen(pwc_name);
        int size_with_null = size + 1;
        //wcsncpy(array_wc_not_const, pwc_name, size);
        wcsncpy(retNames.names[i].wc_name, pwc_name, size_with_null);
        //for (int j = 0;j < 256;j++)
        //    retNames.names[i].wc_name[j] = pwc_name[j];
    }

    retNames.n_num_of_values = i;

    return retNames;
}

struct strAFDictKeys GetKeysFromGodict(godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg)
{
    struct strAFDictKeys retKeys;

    godot_dictionary godict_arg = (*pgodict_arg);
    godot_array godarray_keys = api_arg->godot_dictionary_keys(&godict_arg);
    godot_int godint_size_of_godarray_keys = api_arg->godot_array_size(&godarray_keys);

    printf("Size of array: %d \n", godint_size_of_godarray_keys);

    int i = 0;
    for (i = 0;i < godint_size_of_godarray_keys;i++)
    {
        godot_variant godvar_my_key;
        godvar_my_key = api_arg->godot_array_get(&godarray_keys, i);
        godot_string godstring_key = api_arg->godot_variant_as_string(&godvar_my_key);

        const wchar_t* pwc_key = api_arg->godot_string_wide_str(&godstring_key);
        wchar_t array_wc_not_const[256];
        //int size = (*pwc_key).size();    
        int size = wcslen(pwc_key);
        int size_with_null = size + 1;
        //wcsncpy(array_wc_not_const, pwc_key, size);
        wcsncpy(retKeys.keys[i].wc_name, pwc_key, size_with_null);
        //for (int j = 0;j < 256;j++)
        //    retKeys.keys[i].wc_name[j] = pwc_key[j];
        
        ////struct strAFName strName;
        //int j = 0;
        //for (j=0;j<256;j++)
        //{
        //    //strName.wc_name[j] = array_wc_not_const;
        //    retKeys.keys[i].wc_name[j] = array_wc_not_const[j];
        //}       
        //
    }

    retKeys.n_num_of_keys = i;    
    
    return retKeys;
}

struct strAFName GetNameFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg)
{
    struct strAFName retName;

    godot_dictionary godict_arg = (*pgodict_arg);

    godot_variant govar_key = GetGovarFromAFName(pgodict_key, api_arg);
    
    godot_variant govar_value = api_arg->godot_dictionary_get(&godict_arg, &govar_key);    
    
    retName = GetAFNameFromGovar(govar_value, api_arg);
    
    return retName;
}

double GetNumberFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg)
{    

    godot_dictionary godict_arg = (*pgodict_arg);

    godot_variant govar_key = GetGovarFromAFName(pgodict_key, api_arg);

    godot_variant govar_value = api_arg->godot_dictionary_get(&godict_arg, &govar_key);

    godot_real godreal_value = api_arg->godot_variant_as_real(&govar_value);
    
    float dValueDouble = godreal_value;

    return dValueDouble;
}


struct strAFNames GetNamesFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg)
{
    struct strAFNames retNames;

    godot_dictionary godict_arg = (*pgodict_arg);

    godot_variant govar_key = GetGovarFromAFName(pgodict_key, api_arg);

    godot_variant govar_value = api_arg->godot_dictionary_get(&godict_arg, &govar_key);

    retNames = GetAFNamesFromGovar(govar_value, api_arg);

    return retNames;
}

godot_dictionary GetGodictFromGodict(const struct strAFName* pgodict_key, godot_dictionary* pgodict_arg, const godot_gdnative_core_api_struct* api_arg)
{
    godot_dictionary godict_arg = (*pgodict_arg);
    godot_variant govar_key = GetGovarFromAFName(pgodict_key, api_arg);
    godot_variant govar_value = api_arg->godot_dictionary_get(&godict_arg, &govar_key);

    godot_dictionary godict_value = api_arg->godot_variant_as_dictionary(&govar_value);

    struct strAFDictKeys keys = GetKeysFromGodict(&godict_value, api_arg);

    return godict_value;
}



//Fin de los métodos para leer diccionarios de godot
///////////////////////////////////////////////////////


///////////////////////////////////////////////////////
//Inicio de los métodos para copiar wchar_t
struct strAFName GetNameFromWChar(wchar_t wc_name[256])
{
    struct strAFName retName;    
    int size = wcslen(wc_name);
    int size_with_null = size + 1;    
    wcsncpy(retName.wc_name, wc_name, size_with_null);
    return retName;
}

//
///////////////////////////////////////////////////////


