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