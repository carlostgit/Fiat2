#ifndef CTRADECALCULATORSCENARIO_H
#define CTRADECALCULATORSCENARIO_H

#include "Market.h"
#include "Reality.h"
#include "TradeCalculator.h"

#include <vector>
#include <memory>
#include <string>

namespace pca
{
    class CPerson;
    class CPrices;
    class CMarket;
    class CReality;
    class CTradeCalculator;

    class CTradeCalculatorScenario
    {
    public:
        CTradeCalculatorScenario();
        virtual ~CTradeCalculatorScenario();

        static int GetTestPrice();

        ////////////////
        //Crear un escenario para ajustar precios, paso a paso
        void CreateEmptyMarket();
        void CreateEmptyReality();
        void CreateTradeCalculator();
        void CreateProduct(std::string sProductName);
        void SetCurrency(std::string sProductName);
        void AddToProduct_CreateConsumptionOption(std::string sProduct ,std::string sOption);
        //void AddToMarket_CreatePerson(std::string sPerson);
        //void AddToPerson_SetProductAmount(std::string sPerson, std::string sProduct, double dAmount);
        //void AddToPerson_SetSatisfactionCurveForOption(std::string sPerson, std::string sOption, double dValueAt0, double dMaxValue);

        void SetSatisfactionCurveForOption(std::string sOption, double dValueAt0, double dMaxValue);

        //
        ///////////////
        //TODO: Hacer método que reciba el escenario en una sola estructura

        //


        //Métodos para obtener información del escenario
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

        /////////////
        //Para hacer cálculos de TradeCalculator, sin generar un escenario con personas
        //
        /*void CreateEmptyMarket();
        void CreateEmptyReality();
        void CreateProduct(std::string sProductName);
        void SetCurrency(std::string sProductName);
        void AddToProduct_CreateConsumptionOption(std::string sProduct, std::string sOption);*/        
        //std::map<COption*, double>  AdjustBestCombidictWithTradeCalculator(structTradeCalculatorScenario* sTradCalculatorScenario);

        std::map<pca::COption*, double> AdjustBestCombidict(double dBudgetArg, std::map<pca::COption*, double> mapCurrentCombidictArg, double dBudgetStepArg, int nMaxStepArg);
       
    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos
        
        std::unique_ptr<CReality> m_upReality;        

        std::unique_ptr<CTradeCalculator> m_upTradeCalculator;

    };
}

#endif // CTRADECALCULATORSCENARIO_H
