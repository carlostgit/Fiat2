#pragma once
#ifdef PRICECALCULATORDLL_EXPORTS
#define PRICECALCULATORDLL_API __declspec(dllexport)
#else
#define PRICECALCULATORDLL_API __declspec(dllimport)
#endif

typedef long(*fpGetTestPriceFromDLL)();
extern "C" PRICECALCULATORDLL_API long GetTestPriceFromDLL();

typedef long(*fpGetTestPriceFromDLL2)(long);
extern "C" PRICECALCULATORDLL_API long GetTestPriceFromDLL2(long nArg);

typedef void(*fpCreateEmptyMarketFromDLL)();
extern "C" PRICECALCULATORDLL_API void CreateEmptyMarketFromDLL();


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
