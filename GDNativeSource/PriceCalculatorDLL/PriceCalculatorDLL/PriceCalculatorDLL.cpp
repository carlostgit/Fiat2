#include "pch.h"
#include "PriceCalculatorDLL.h"

//includes para las llamadas a PriceCalculator
#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"
#include "../../PriceCalculator/src/Tester.h"

long GetTestPriceFromDLL()
{
	//TODO
	//Desde aquí llamar a algún método de PriceCalculator.h

	//LLamada de prueba a Tester de PriceCalculator
	int Test_SatisfactionCurve();

	return 7;
}

long GetTestPriceFromDLL2(long nArg)
{
	//TODO
	//Desde aquí llamar a algún método de PriceCalculator.h

	long nTestPrice = pca::CPriceCalculator::GetTestPrice();

	return 7 + nArg + nTestPrice;
}

void CreateEmptyMarketFromDLL()
{
	pca::CPriceCalculatorStaticUser::CreateEmptyMarket();
}

void CreateProductFromDLL(std::string sProductName)
{
	pca::CPriceCalculatorStaticUser::CreateProduct(sProductName);
}

void SetCurrencyFromDLL(std::string sProductName)
{
	pca::CPriceCalculatorStaticUser::SetCurrency(sProductName);
}

void AddToProduct_CreateConsumptionOptionFromDLL(std::string sProduct, std::string sOption)
{
	pca::CPriceCalculatorStaticUser::AddToProduct_CreateConsumptionOption(sProduct, sOption);
}

void AddToMarket_CreatePersonFromDLL(std::string sPerson)
{
	pca::CPriceCalculatorStaticUser::AddToMarket_CreatePerson(sPerson);
}

void AddToPerson_SetProductAmountFromDLL(std::string sPerson, std::string sProduct, double dAmount)
{
	pca::CPriceCalculatorStaticUser::AddToPerson_SetProductAmount(sPerson, sProduct, dAmount);
}

void AddToPerson_SetSatisfactionCurveForOptionFromDLL(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
{
	pca::CPriceCalculatorStaticUser::AddToPerson_SetSatisfactionCurveForOption(sPerson, sOption, dValueAt0, dMaxValue);
}

void AdjustPricesFromDLL()
{
	pca::CPriceCalculatorStaticUser::AdjustPrices();
}

bool IsProductFromDLL(std::string sProductName)
{
	return pca::CPriceCalculatorStaticUser::IsProduct(sProductName);
}

bool IsPersonFromDLL(std::string sPersonName)
{
	return pca::CPriceCalculatorStaticUser::IsPerson(sPersonName);
}

bool IsOptionFromDLL(std::string sOptionName)
{
	return pca::CPriceCalculatorStaticUser::IsOption(sOptionName);
}

std::string GetCurrencyFromDLL()
{
	return pca::CPriceCalculatorStaticUser::GetCurrency();
}

double GetPriceFromDLL(std::string sProductName)
{
	return pca::CPriceCalculatorStaticUser::GetPrice(sProductName);
}

double GetProductAmountFromDLL(std::string sProductName, std::string sPerson)
{
	return pca::CPriceCalculatorStaticUser::GetProductAmount(sProductName, sPerson);
}

double GetOptionAmountFromDLL(std::string sOptionName, std::string sPerson)
{
	return pca::CPriceCalculatorStaticUser::GetOptionAmount(sOptionName, sPerson);
}

void PrintPricesEvolutionFromDLL()
{
	return pca::CPriceCalculatorStaticUser::PrintPricesEvolution();
}

double GetDesiredProdAmountFromDLL(std::string sPerson, pca::CProduct* pProduct)
{
	return GetDesiredProdAmountFromDLL(sPerson, pProduct);
}

void PrintPersonOptionAdjustmentToFileFromDLL(std::string sPerson)
{
	PrintPersonOptionAdjustmentToFile(sPerson)
}

void PrintPersonOptionAdjustmentToFileFromDLL()
{
	PrintPersonOptionAdjustmentToFile();
}

