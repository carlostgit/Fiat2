
#include "PriceCalculatorStaticUser.h"

pca::CPriceCalculator pca::CPriceCalculatorStaticUser::m_oPriceCalculator;

pca::CPriceCalculatorStaticUser::~CPriceCalculatorStaticUser()
{

}

void pca::CPriceCalculatorStaticUser::CreateEmptyMarket()
{
	m_oPriceCalculator.CreateEmptyMarket();
}

void pca::CPriceCalculatorStaticUser::CreateProduct(std::string sProductName)
{
	m_oPriceCalculator.CreateProduct(sProductName);
}

void pca::CPriceCalculatorStaticUser::SetCurrency(std::string sProductName)
{
	m_oPriceCalculator.SetCurrency(sProductName);
}

void pca::CPriceCalculatorStaticUser::AddToProduct_CreateConsumptionOption(std::string sProduct, std::string sOption)
{
	m_oPriceCalculator.AddToProduct_CreateConsumptionOption(sProduct,sOption);
}

void pca::CPriceCalculatorStaticUser::AddToMarket_CreatePerson(std::string sPerson)
{
	m_oPriceCalculator.AddToMarket_CreatePerson(sPerson);
}

void pca::CPriceCalculatorStaticUser::AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount)
{
	m_oPriceCalculator.AddToPerson_SetProductAmount(sPerson, sProduct, dAmount);
}

void pca::CPriceCalculatorStaticUser::AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue)
{
	m_oPriceCalculator.AddToPerson_SetSatisfactionCurveForOption(sPerson, sOption, dValueAt0, dMaxValue);
}
	 
void pca::CPriceCalculatorStaticUser::AdjustPrices()
{
	m_oPriceCalculator.AdjustPrices();
}
	 
bool pca::CPriceCalculatorStaticUser::IsProduct(std::string sProductName)
{
	return m_oPriceCalculator.IsProduct(sProductName);
}

bool pca::CPriceCalculatorStaticUser::IsPerson(std::string sPersonName)
{
	return m_oPriceCalculator.IsPerson(sPersonName);
}

bool pca::CPriceCalculatorStaticUser::IsOption(std::string sOptionName)
{
	return m_oPriceCalculator.IsOption(sOptionName);
}

std::string pca::CPriceCalculatorStaticUser::GetCurrency()
{
	return m_oPriceCalculator.GetCurrency();
}

double pca::CPriceCalculatorStaticUser::GetPrice(std::string sProductName)
{
	return m_oPriceCalculator.GetPrice(sProductName);
}

double pca::CPriceCalculatorStaticUser::GetProductAmount(std::string sProductName, std::string sPerson)
{
	return m_oPriceCalculator.GetProductAmount(sProductName, sPerson);
}

double pca::CPriceCalculatorStaticUser::GetOptionAmount(std::string sOptionName, std::string sPerson)
{
	return m_oPriceCalculator.GetOptionAmount(sOptionName, sPerson);
}

void pca::CPriceCalculatorStaticUser::PrintPricesEvolution()
{
	m_oPriceCalculator.PrintPricesEvolution();
}

double pca::CPriceCalculatorStaticUser::GetDesiredProdAmount(std::string sPerson, std::string sProductName)
{
	return m_oPriceCalculator.GetDesiredProdAmount(sPerson, sProductName);
}

void pca::CPriceCalculatorStaticUser::PrintPersonOptionAdjustmentToFile(std::string sPerson)
{
	m_oPriceCalculator.PrintPersonOptionAdjustmentToFile(sPerson);
}

void pca::CPriceCalculatorStaticUser::PrintPersonOptionAdjustmentToFile()
{
	m_oPriceCalculator.PrintPersonsOptionAdjustmentToFile();
}

