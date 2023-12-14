#include <gdnative_api_struct.gen.h>
#include <string.h>
#include "BindToCPP.h"
#include <stdio.h>
#include <windows.h>
//Prueba con libreria Market.dll
//#include "../../Market/market.h"
//tipo del método
//void DLL_EXPORT SomeFunction(const LPCSTR sometext);
//DWORD(*Arithmetic)(DWORD, DWORD);
//void(*SomeFunction)(const LPCSTR sometext);
typedef void(*SomeF)(const LPCSTR sometext);
//

//

//Callback para pasarse como puntero como argumento del método
// setCallbackMethodForPrices de MarketTest
void setDataFromMarket(int nProduct, double dAmount);


//Variable global para guardar los resultados que llegan en setPrice
//Es como otro user_data_struct
double g_dDataFromMarket = 0.0;
//

typedef struct user_data_struct {
	char data[256];
} user_data_struct;

// GDNative supports a large collection of functions for calling back
// into the main Godot executable. In order for your module to have
// access to these functions, GDNative provides your application with
// a struct containing pointers to all these functions.
const godot_gdnative_core_api_struct *api = NULL;
const godot_gdnative_ext_nativescript_api_struct *nativescript_api = NULL;

// These are forward declarations for the functions we'll be implementing
// for our object. A constructor and destructor are both necessary.
GDCALLINGCONV void *simple_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void simple_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);
godot_variant simple_get_data(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant simple_get_data2(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant simple_set_and_get_data(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant simple_get_num_args(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant simple_get_and_set_dict(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
//godot_variant simple_calc_info_from_market_test(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
godot_variant simple_calc_info_from_price_calculator_dll(godot_object* p_instance, void* p_method_data, void* p_user_data, int p_num_args, godot_variant** p_args);


// `gdnative_init` is a function that initializes our dynamic library.
// Godot will give it a pointer to a structure that contains various bits of
// information we may find useful among which the pointers to our API structures.
void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *p_options) {
	api = p_options->api_struct;


//    printf("Before libr_path:\n");
//    godot_string* libr_path = p_options->active_library_path;
//    printf("after libr_path:\n");
//    api->godot_print(libr_path);


	// Find NativeScript extensions.
	for (int i = 0; i < api->num_extensions; i++) {
		switch (api->extensions[i]->type) {
			case GDNATIVE_EXT_NATIVESCRIPT: {
				nativescript_api = (godot_gdnative_ext_nativescript_api_struct *)api->extensions[i];
			}; break;
			default:
				break;
		};
	};
}

// `gdnative_terminate` which is called before the library is unloaded.
// Godot will unload the library when no object uses it anymore.
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *p_options) {
	api = NULL;
	nativescript_api = NULL;
	//api12 = NULL;
}

// `nativescript_init` is the most important function. Godot calls
// this function as part of loading a GDNative library and communicates
// back to the engine what objects we make available.
void GDN_EXPORT godot_nativescript_init(void *p_handle) {
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &simple_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &simple_destructor;

	// We first tell the engine which classes are implemented by calling this.
	// * The first parameter here is the handle pointer given to us.
	// * The second is the name of our object class.
	// * The third is the type of object in Godot that we 'inherit' from;
	//   this is not true inheritance but it's close enough.
	// * Finally, the fourth and fifth parameters are descriptions
	//   for our constructor and destructor, respectively.
	nativescript_api->godot_nativescript_register_class(p_handle, "PRICECALCULATORGDNBIND", "Reference", create, destroy);

	godot_instance_method get_data = { NULL, NULL, NULL };
	get_data.method = &simple_get_data;

	godot_instance_method get_data2 = { NULL, NULL, NULL };
    get_data2.method = &simple_get_data2;

    godot_instance_method set_and_get_data = { NULL, NULL, NULL };
    set_and_get_data.method = &simple_set_and_get_data;

    godot_instance_method get_num_args = { NULL, NULL, NULL };
    get_num_args.method = &simple_get_num_args;

    godot_instance_method get_and_set_dict = { NULL, NULL, NULL };
    get_and_set_dict.method = &simple_get_and_set_dict;

    //godot_instance_method calc_info_from_market_test = { NULL, NULL, NULL };
    //calc_info_from_market_test.method = &simple_calc_info_from_market_test;

    godot_instance_method calc_info_from_price_calculator_dll = { NULL, NULL, NULL };
    calc_info_from_price_calculator_dll.method = &simple_calc_info_from_price_calculator_dll;

	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

	// We then tell Godot about our methods by calling this for each
	// method of our class. In our case, this is just `get_data`.
	// * Our first parameter is yet again our handle pointer.
	// * The second is again the name of the object class we're registering.
	// * The third is the name of our function as it will be known to GDScript.
	// * The fourth is our attributes setting (see godot_method_rpc_mode enum in
	//   `godot_headers/nativescript/godot_nativescript.h` for possible values).
	// * The fifth and final parameter is a description of which function
	//   to call when the method gets called.
	nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "get_data", attributes, get_data);
	nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "get_data2", attributes, get_data2);
	nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "set_and_get_data", attributes, set_and_get_data);
	nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "get_num_args", attributes, get_num_args);
	nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "get_and_set_dict", attributes, get_and_set_dict);
	//nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "calc_info_from_market_test", attributes, calc_info_from_market_test);
    nativescript_api->godot_nativescript_register_method(p_handle, "PRICECALCULATORGDNBIND", "calc_info_from_price_calculator_dll", attributes, calc_info_from_price_calculator_dll);
}

// In our constructor, allocate memory for our structure and fill
// it with some data. Note that we use Godot's memory functions
// so the memory gets tracked and then return the pointer to
// our new structure. This pointer will act as our instance
// identifier in case multiple objects are instantiated.
GDCALLINGCONV void *simple_constructor(godot_object *p_instance, void *p_method_data) {
	user_data_struct *user_data = api->godot_alloc(sizeof(user_data_struct));
	strcpy_s(user_data->data, sizeof(user_data_struct), "Hellow frome SimpleMod!");

	return user_data;
}

// The destructor is called when Godot is done with our
// object and we free our instances' member data.
GDCALLINGCONV void simple_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	api->godot_free(p_user_data);
}

// Data is always sent and returned as variants so in order to
// return our data, which is a string, we first need to convert
// our C string to a Godot string object, and then copy that
// string object into the variant we are returning.
godot_variant simple_get_data(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	godot_string data;
	godot_variant ret;
	user_data_struct *user_data = (user_data_struct *)p_user_data;

	api->godot_string_new(&data);
	api->godot_string_parse_utf8(&data, user_data->data);
	api->godot_variant_new_string(&ret, &data);
	api->godot_string_destroy(&data);

	return ret;
}


godot_variant simple_get_data2(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
	godot_string data;

	godot_variant ret;
	//user_data_struct *user_data = (user_data_struct *)p_user_data;
	api->godot_string_new(&data);
	//api->godot_string_parse_utf8(&data, user_data->data);

	//char mi_char_string[256] = "bla bla bla bla";

	//api->godot_string_parse_utf8(&data, mi_char_string);
	api->godot_string_parse_utf8(&data, "blab lab la blala ldalfjasj akd ald ld lajdjasj ");
	//string miString = "simple_get_data2";
	api->godot_variant_new_string(&ret, &data);
	api->godot_string_destroy(&data);

	return ret;
}

godot_variant simple_set_and_get_data(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
    godot_variant ret;

    godot_string myString = api->godot_variant_as_string(*p_args);

    godot_string myString2;

    const wchar_t* myWchar_t = api->godot_string_wide_str(&myString);

    godot_int length = api->godot_string_length(&myString);

    wchar_t myStringPur[200] = L"myStringPur";

    godot_int length2 = wcslen(myStringPur);

    int i = 0;
    for (i = 0;i<length && i<length2;i++)
    {
        myStringPur[i]=myWchar_t[i];
    }

    api->godot_string_new_with_wide_string(&myString2, &myStringPur, length2);

    api->godot_variant_new_string(&ret, &myString2);

	return ret;
}

godot_variant simple_get_num_args(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
    godot_variant ret;

    godot_string myStringNumArgs = api->godot_string_num((double)p_num_args);

    api->godot_variant_new_string(&ret, &myStringNumArgs);

	return ret;
}

godot_variant simple_get_and_set_dict(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
{
    //Recibo un diccionario, y devuelvo otro, cambiando el valor del elemento,
    //con key "cucu" por un 17.

    //TODO: Ordenar esto un poco, y hacer algo parecido con diccionarios que
    //contengan arrays. Ya con eso, creo que podría hacer mucho

    //También podría probar a convertir todo a un json, y usar un json
    //como argumento, y como respuesta.


    godot_variant godvar_ret;

//    printf("Godot version mayor:%d, minor%d\n", api->version.major,api->version.minor);
//    printf("type: %d\n",api->type);
//    printf("num extensions: %d\n",api->num_extensions);
//    int iext=0;
//    printf("Extensions:\n");
//
//    for (iext=0;iext<api->num_extensions;iext++)
//    {
//        printf("iext: %d\n",iext);
//        printf("type: %d\n",api->extensions[iext]->type);
//        printf("extension version mayor:%d, minor%d\n", api->extensions[iext]->version.major,api->extensions[iext]->version.minor);
//    }

    godot_dictionary godict_arg = api->godot_variant_as_dictionary(*p_args);

    godot_dictionary godict_arg_copy;
    api->godot_dictionary_new_copy(&godict_arg_copy, &godict_arg);
    //Esta copia sobraba. No funciona como se espera de una copia.
    //Si modifico arg_dict_copy, se modifica también el diccionario recibido como argumento


    //////////
    //Copia manual
    //Primero copio manualmente el diccionario, y luego cambiaré el valor de cucu
    //Tengo que copiar el diccionario elemento a elemento, a mano, porque no tengo
    //acceso a la estructura godot_gdnative_core_1_2_api_struct que es la
    //que tiene el método godot_dictionary_duplicate
    //Y el método copy, parece que no duplica. Cuando modificas
    //la copia, ves que se modifica el original también
    godot_dictionary godict_arg_man_copy;
    {
        api->godot_dictionary_new(&godict_arg_man_copy);

        godot_array godarray_keys = api->godot_dictionary_keys(&godict_arg);
        godot_array godarray_values = api->godot_dictionary_values(&godict_arg);

        godot_int godint_size_of_array = api->godot_array_size(&godarray_keys);

        printf("Size of array: %d \n", godint_size_of_array);

        int i=0;
        for(i=0;i<godint_size_of_array;i++)
        {
            //No sé si hace falta copiar los strings como lo hago aquí
            //No sé qué tipo de copia se hace con los variant, si paso la referencia directamente
            //desde el diccionario origen
            godot_variant godvar_my_key;
            godvar_my_key = api->godot_array_get(&godarray_keys,i);
            godot_string godstring_key = api->godot_variant_as_string(&godvar_my_key);
            api->godot_print(&godstring_key);

            godot_variant godvar_my_value;
            godvar_my_value = api->godot_array_get(&godarray_values,i);
            godot_string godstring_value = api->godot_variant_as_string(&godvar_my_value);
            api->godot_print(&godstring_value);

            godot_variant godvar_my_key2 = godvar_my_key;
            godot_variant godvar_my_value2 = godvar_my_value;

            api->godot_variant_new_copy(&godvar_my_key2,&godvar_my_key);
            godot_string godstring_key2 = api->godot_variant_as_string(&godvar_my_key2);
            api->godot_variant_new_copy(&godvar_my_value2,&godvar_my_value);
            godot_string godstring_value2 = api->godot_variant_as_string(&godvar_my_value2);

            printf("my key 2: ");
            api->godot_print(&godstring_key2);
            printf("my value 2:%d\n",godvar_my_value2);
            api->godot_print(&godstring_value2);

            api->godot_dictionary_set(&godict_arg_man_copy, &godvar_my_key2, &godvar_my_value2);
            printf("after set");

        }
    }
    //Fin de copia manual
    //////

    ////
    //Pongo un valor 17 al elemento con key cucu
    {
        wchar_t wchar_cucu[10] = L"cucu";
        godot_int godint_cucu_length = wcslen(wchar_cucu);
        godot_string godstring_cucu;
        api->godot_string_new_with_wide_string(&godstring_cucu, &wchar_cucu, godint_cucu_length);
        //Supongo que estos strings se copian, y que da igual que luego destruya el wchar_cucu
        api->godot_print(&godstring_cucu);

        godot_variant godvar_cucu;
        api->godot_variant_new_string(&godvar_cucu,&godstring_cucu);

        godot_bool bool_has_cucu = api->godot_dictionary_has(&godict_arg, &godvar_cucu);
        printf("bool_has_cucu %d \n",bool_has_cucu);

        if (bool_has_cucu)
        {
            double d_new_value_for_cucu = 84;

            godot_variant godvar_new_value_for_cucu;
            api->godot_variant_new_real(&godvar_new_value_for_cucu, d_new_value_for_cucu);

            //godot_variant value_of_cucu = api->godot_dictionary_get(&godict_arg_man_copy, &godvar_cucu);
            api->godot_dictionary_set(&godict_arg_man_copy, &godvar_cucu, &godvar_new_value_for_cucu);
        }
    }
    //Fin de poner un 17 donde cucu
    //////


    //////
    //Cambiar el array que hay en el key caca, para añadir un elemento con valor c al array
    {
        wchar_t wchar_caca[10] = L"caca";
        godot_int godint_caca_length = wcslen(wchar_caca);
        godot_string godstring_caca;
        api->godot_string_new_with_wide_string(&godstring_caca, &wchar_caca, godint_caca_length);
        api->godot_print(&godstring_caca);
        godot_variant godvar_caca;
        api->godot_variant_new_string(&godvar_caca,&godstring_caca);


        godot_bool bool_has_caca = api->godot_dictionary_has(&godict_arg, &godvar_caca);
        printf("bool_has_caca %d \n",bool_has_caca);

        if (bool_has_caca)
        {
            //Nuevo valor a añadir al array
            wchar_t wchar_c[5] = L"c";
            godot_int godint_c_length = wcslen(wchar_c);
            godot_string godstring_c;
            api->godot_string_new_with_wide_string(&godstring_c, &wchar_c, godint_c_length);
            api->godot_print(&godstring_c);
            godot_variant godvar_c;
            api->godot_variant_new_string(&godvar_c,&godstring_c);

            //Obtener el array actual
            godot_variant govar_old_array = api->godot_dictionary_get(&godict_arg,&godvar_caca);

            godot_array godarray_old_array =  api->godot_variant_as_array(&govar_old_array);

            //voy a hacer una copia, para no alterar el antiguo array. Pq el tipo
            //de copia que he hecho de los diccionarios, es solo del puntero al array

            godot_array godarray_new_array;
            api->godot_array_new(&godarray_new_array);

            godot_variant govar_new_array;
            api->godot_variant_new_array(&govar_new_array,&godarray_new_array);

            //Copio los viejos elementos

            godot_int godint_old_array_size = api->godot_array_size(&godarray_old_array);
            int i=0;
            for(i=0;i<godint_old_array_size;i++)
            {
                //godot_variant *(*godot_array_operator_index)(godot_array *p_self, const godot_int p_idx);

                godot_variant* pGovar_old_elem = api->godot_array_operator_index(&godarray_old_array,i);

                api->godot_array_append(&godarray_new_array, pGovar_old_elem);
            }

            //Añado el nuevo elemento
            api->godot_array_append(&godarray_new_array, &godvar_c);


            //Sustituyo en viejo array por el nuevo
            api->godot_dictionary_set(&godict_arg_man_copy,&godvar_caca,&govar_new_array);

        }


    }
    //Fin de añader una c en el array que hay en el key caca
    //////

    api->godot_variant_new_dictionary(&godvar_ret, &godict_arg_man_copy);





	return godvar_ret;
}



//godot_variant simple_calc_info_from_market_test(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args)
//{
//    godot_variant godvar_ret;
//
//    market_addPriceForProduct(2,34.6);
//    //Test de registro de callback
//    market_setCallbackMethodForPrices(&setDataFromMarket);
//    market_calculationTest(35);
//
//    double d_new_value = g_dDataFromMarket;
//    api->godot_variant_new_real(&godvar_ret, d_new_value);
//
//    //Pruebo a llamar a un método de Market.dll
//    //He comprobado, q carga la librería, solo si la pongo en el exe de godot
//    //Ejemplo con run-time inking. Creo que no es necesario compilar linkando
//    //con la librería estática
//    //HMODULE hDll = LoadLibrary(_T("Marketd.dll"));
//    HMODULE hDll = LoadLibrary("Marketd.dll");
//    if (!hDll || hDll == INVALID_HANDLE_VALUE) {
//        printf("unable to load libraray\n");
//        //wchar_t wchar_caca[20] = L"unable to load libraray";
//        wchar_t wchar_caca[24] = L"unable to load libraray";
//        godot_int godint_caca_length = wcslen(wchar_caca);
//        godot_string godstring_caca;
//        api->godot_string_new_with_wide_string(&godstring_caca, &wchar_caca, godint_caca_length);
//        api->godot_print(&godstring_caca);
//        return godvar_ret;
//    }
//
//    printf("Marketd.dll loaded\n");
//
//    void(*functionPtr)(const LPCSTR sometext);
//    functionPtr = (SomeF)(GetProcAddress(hDll, "SomeFunction"));
//    //Lo anterior queda más bonito, pero también se puede hacer
//    //como en la siguiente linea, sin usar el typdef
//    //functionPtr = (void(*)(const LPCSTR sometext))(GetProcAddress(hDll, "SomeFunction"));
//
//    functionPtr("Hello from run-time linked dll");
//    //Fin del ejemplo con run-time linking.
//
//	return godvar_ret;
//}

//Metodo callback para que lo use MarketTest
void setDataFromMarket(int nProduct, double dAmount)
{
    printf("nProduct: %d",nProduct );
    printf("dAmount: %d",dAmount);
    g_dDataFromMarket = dAmount;
}

godot_variant simple_calc_info_from_price_calculator_dll(godot_object* p_instance, void* p_method_data, void* p_user_data, int p_num_args, godot_variant** p_args)
{
    godot_variant godvar_ret;

    //double d_new_value = g_
   // api->godot_variant_new_real(&godvar_ret, d_new_value);

    //int int_ret_from_price_calculator_dll = test_price_calculator_dll();

    struct strProductAmount strRet;
    test_price_calculator_dll_with_str(&strRet);

    int int_ret_from_price_calculator_dll = strRet.nProductId;
    double double_ret_from_price_calculator_dll = strRet.dAmount;

    //wchar_t wchar_ret_from_price_calculator_dll[20];
    //swprintf(wchar_ret_from_price_calculator_dll, "%d", int_ret_from_price_calculator_dll);

    //godot_string godstring_to_print;
    //godot_int godint_text_length = wcslen(wchar_ret_from_price_calculator_dll);
    //api->godot_string_new_with_wide_string(&godstring_to_print, &wchar_ret_from_price_calculator_dll, godint_text_length);
    //api->godot_print(&godstring_to_print);
    
    //api->godot_variant_new_int(&godvar_ret ,int_ret_from_price_calculator_dll);
    api->godot_variant_new_real(&godvar_ret, double_ret_from_price_calculator_dll);

    return godvar_ret;
}
