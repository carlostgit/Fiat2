#ifndef CPRICECALCULATOR_H
#define CPRICECALCULATOR_H

#include "Market.h"

#include <vector>
#include <memory>



namespace pca
{
    class CPerson;
    class CPrices;
    class CMarket;

    class CPriceCalculator
    {
    public:
        CPriceCalculator();
        virtual ~CPriceCalculator();


        static int GetTestPrice();

        /* 
        Idea de cómo se podría generar un escenario simple
        CreateEmptyMarket();

        AddToMarket_CreateProduct("nut");
        AddToProduct_CreateConsumptionOption("nut consumption")

        AddToMarket_CreateProduct("chocolate");
        AddToProduct_CreateConsumptionOptionOfProduct("chocolate consumption")

        AddToMarket_CreateProduct("candy");
        AddToProduct_CreateConsumptionOptionOfProduct("candy consumption")

        AddToMarket_CreatePerson("pepe")
        AddToPerson_SetProductAmount("nut", amount_of_nut)
        AddToPerson_SetProductAmount("chocolate", amount_of_chocolate)
        AddToPerson_SetProductAmount("candy", amount_of_candy)
        AddToPerson_SetSatisfactionCurveForOption("nut consumption", valueAt0, maxValue)
        AddToPerson_SetSatisfactionCurveForOption("chocolate consumption", valueAt0, maxValue)
        AddToPerson_SetSatisfactionCurveForOption("candy consumption", valueAt0, maxValue)

        AddToMarket_CreatePerson("juan")
        AddToPerson_SetProductAmount("nut", amount_of_nut)
        AddToPerson_SetProductAmount("chocolate", amount_of_chocolate)
        AddToPerson_SetProductAmount("candy", amount_of_chocolate)
        AddToPerson_SetSatisfactionCurveForOption("nut consumption", valueAt0, maxValue)
        AddToPerson_SetSatisfactionCurveForOption("chocolate consumption", valueAt0, maxValue)
        AddToPerson_SetSatisfactionCurveForOption("candy consumption", valueAt0, maxValue)
        
        AdjustPrices()
        
        */


       
    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos

        std::unique_ptr<CMarket> m_upMarket;
        

    };
}

#endif // CPRICECALCULATOR_H
