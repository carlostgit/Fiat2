#ifndef CPRICECALCULATOR_H
#define CPRICECALCULATOR_H

#include "Market.h"
#include "Reality.h"

#include <vector>
#include <memory>
#include <string>

namespace pca
{
    class CPerson;
    class CPrices;
    class CMarket;
    class CReality;

    class CPriceCalculator
    {
    public:
        CPriceCalculator();
        virtual ~CPriceCalculator();

        static int GetTestPrice();

        void CreateEmptyMarket();
        void CreateEmptyReality();
        void CreateProduct(std::string sProductName);
        void SetCurrency(std::string sProductName);
        void AddToProduct_CreateConsumptionOption(std::string sProduct ,std::string sOption);
        void AddToMarket_CreatePerson(std::string sPerson);
        void AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount);
        void AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue);

        void AdjustPrices();

        bool IsProduct(std::string sProductName);
        bool IsPerson(std::string sPersonName);
        bool IsOption(std::string sOptionName);
        std::string GetCurrency();

        double GetPrice(std::string sProductName);
        double GetProductAmount(std::string sProductName, std::string sPerson);
        double GetOptionAmount(std::string sOptionName, std::string sPerson);
        double GetTradedAmount(std::string sProductName, std::string sPerson);

        void PrintPricesEvolution();

        double GetDesiredProdAmount(std::string sPerson, std::string sProductName);
        void PrintPersonOptionAdjustmentToFile(std::string sPerson);
        void PrintPersonsOptionAdjustmentToFile();        
       
    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos
        
        std::unique_ptr<CReality> m_upReality;        

    };
}

#endif // CPRICECALCULATOR_H
