#ifndef CPRICECALCULATORSTATICUSER_H
#define CPRICECALCULATORSTATICUSER_H

#include "Market.h"
#include "PriceCalculator.h"

#include <vector>
#include <memory>
#include <string>



namespace pca
{
    class CPerson;
    class CPrices;
    class CMarket;

    class CPriceCalculatorStaticUser
    {
    public:
        CPriceCalculatorStaticUser() {}
        virtual ~CPriceCalculatorStaticUser();

        static pca::CPriceCalculator* GetPriceCalculatorRef(){
            return &m_oPriceCalculator;
        }

        //static void CreateEmptyMarket();
        //static void CreateEmptyReality();
        //static void CreateProduct(std::string sProductName);
        //static void SetCurrency(std::string sProductName);
        //static void AddToProduct_CreateConsumptionOption(std::string sProduct ,std::string sOption);
        //static void AddToMarket_CreatePerson(std::string sPerson);
        //static void AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount);
        //static void AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue);

        //static void AdjustPrices();

        //static bool IsProduct(std::string sProductName);
        //static bool IsPerson(std::string sPersonName);
        //static bool IsOption(std::string sOptionName);
        //static std::string GetCurrency();

        //static double GetPrice(std::string sProductName);
        //static double GetProductAmount(std::string sProductName, std::string sPerson);
        //static double GetOptionAmount(std::string sOptionName, std::string sPerson);

        //static void PrintPricesEvolution();

        //static double GetDesiredProdAmount(std::string sPerson, std::string sProductName);
        //static void PrintPersonOptionAdjustmentToFile(std::string sPerson);
        //static void PrintPersonsOptionAdjustmentToFile();

        //pca::CPriceCalculator* GetPriceCalculatorPtr();

    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos

        static CPriceCalculator m_oPriceCalculator;
        

    };
}

#endif // CPRICECALCULATOR_H
