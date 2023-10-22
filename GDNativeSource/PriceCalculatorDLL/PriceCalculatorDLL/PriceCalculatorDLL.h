#pragma once
#ifdef PRICECALCULATORDLL_EXPORTS
#define PRICECALCULATORDLL_API __declspec(dllexport)
#else
#define PRICECALCULATORDLL_API __declspec(dllimport)
#endif

#include <string>


typedef long(*fpGetTestPriceFromDLL)();
extern "C" PRICECALCULATORDLL_API long GetTestPriceFromDLL();

typedef long(*fpGetTestPriceFromDLL2)(long);
extern "C" PRICECALCULATORDLL_API long GetTestPriceFromDLL2(long nArg);

typedef void(*fpCreateEmptyMarketFromDLL)();
extern "C" PRICECALCULATORDLL_API void CreateEmptyMarketFromDLL();

typedef void(*fpCreateProductFromDLL)();
extern "C" PRICECALCULATORDLL_API void CreateProductFromDLL(std::string sProductName);

typedef void(*fpIsProductFromDLL)();
extern "C" PRICECALCULATORDLL_API bool IsProductFromDLL(std::string sProductName);

typedef void(*fpSetCurrencyFromDLL)();
extern "C" PRICECALCULATORDLL_API void SetCurrencyFromDLL(std::string sProductName);

typedef void(*fpAddToProduct_CreateConsumptionOptionFromDLL)();
extern "C" PRICECALCULATORDLL_API void AddToProduct_CreateConsumptionOptionFromDLL(std::string sProduct, std::string sOption);

typedef void(*fpAddToMarket_CreatePersonFromDLL)();
extern "C" PRICECALCULATORDLL_API void AddToMarket_CreatePersonFromDLL(std::string sPerson);

typedef void(*fpAddToPerson_SetProductAmountFromDLL)();
extern "C" PRICECALCULATORDLL_API void AddToPerson_SetProductAmountFromDLL(std::string sPerson, std::string sProduct, double dAmount);

typedef void(*fpAddToPerson_SetSatisfactionCurveForOptionFromDLL)();
extern "C" PRICECALCULATORDLL_API void AddToPerson_SetSatisfactionCurveForOptionFromDLL(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue);

typedef void(*fpAdjustPricesFromDLL)();
extern "C" PRICECALCULATORDLL_API void AdjustPricesFromDLL();

typedef void(*fpIsProductFromDLL)();
extern "C" PRICECALCULATORDLL_API bool IsProductFromDLL(std::string sProductName);

typedef void(*fpIsPersonFromDLL)();
extern "C" PRICECALCULATORDLL_API bool IsPersonFromDLL(std::string sPersonName);

typedef void(*fpIsOptionFromDLL)();
extern "C" PRICECALCULATORDLL_API bool IsOptionFromDLL(std::string sOptionName);

typedef void(*fpGetCurrencyFromDLL)();
extern "C" PRICECALCULATORDLL_API std::string GetCurrencyFromDLL();

typedef void(*fpGetPriceFromDLL)();
extern "C" PRICECALCULATORDLL_API double GetPriceFromDLL(std::string sProductName);

typedef void(*fpGetProductAmountFromDLL)();
extern "C" PRICECALCULATORDLL_API double GetProductAmountFromDLL(std::string sProductName, std::string sPerson);

typedef void(*fpGetOptionAmountFromDLL)();
extern "C" PRICECALCULATORDLL_API double GetOptionAmountFromDLL(std::string sOptionName, std::string sPerson);



//void CreateEmptyMarket();
//void CreateProduct(std::string sProductName);
//void SetCurrency(std::string sProductName);
//void AddToProduct_CreateConsumptionOption(std::string sProduct, std::string sOption);
//void AddToMarket_CreatePerson(std::string sPerson);
//void AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount);
//void AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue);
//
//void AdjustPrices();
//
//bool IsProduct(std::string sProductName);
//bool IsPerson(std::string sPersonName);
//bool IsOption(std::string sOptionName);
//std::string GetCurrency();
//
//double GetPrice(std::string sProductName);
//double GetProductAmount(std::string sProductName, std::string sPerson);
//double GetOptionAmount(std::string sOptionName, std::string sPerson);
