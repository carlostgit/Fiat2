#include "Tester.h"
#include <iostream>
#include "PriceCalculationDefines.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"
#include "Prices.h"
#include "Market.h"
#include "Utils.h"



pca::CTester::CTester()
{
    //ctor

    std::cout << "Creating CTester" << std::endl;
}

pca::CTester::~CTester()
{
    //dtor
}

int pca::CTester::Test_SatisfactionCurve()
{
    std::cout << "Starting Test_SatisfactionCurve" << std::endl;

    CSatisfactionCurve oSatCurve;

    for (int i=0; i<20; i++)
    {
        double dSatisf = oSatCurve.CalculateSatifaction(i);
        std::cout << "dSatisfAt_"<<i << ": "<< dSatisf << std::endl;
    }

    std::cout << "Test_SatisfactionCurve finished" << std::endl;
    
    return 0;
}

int pca::CTester::Test_SatisfactionCalculator()
{
    std::cout << "Starting Test_SatisfactionCalculator" << std::endl;
    {
        CSatisfactionCalculator oSatCalculator;
        std::map<eOpt, double> map_nOption_dAmount;
        for (auto& nOption : c_setOptions)
        {
            map_nOption_dAmount[nOption] = 1.0;
        }

        std::cout << "Prueba..." << std::endl;
        double dSatisfFormIndivOptions = oSatCalculator.CalculateSatisfOfCombidictFromIndividualOptions(map_nOption_dAmount);
        std::cout << "dSatisfFormIndivOptions: " << dSatisfFormIndivOptions << std::endl;
        double dSatisfFormSuppCombos = oSatCalculator.CalculateSatisfOfCombidictFromSupplementaryCombos(map_nOption_dAmount);
        std::cout << "dSatisfFormSuppCombos " << dSatisfFormSuppCombos << std::endl;
        double dSatisfFormCompCombos = oSatCalculator.CalculateSatisfOfCombidictFromComplementaryCombos(map_nOption_dAmount);
        std::cout << "dSatisfFormCompCombos " << dSatisfFormCompCombos << std::endl;
        double dSatisfTotal = oSatCalculator.CalculateSatisfOfCombidict(map_nOption_dAmount);
        std::cout << "dSatisfTotal " << dSatisfTotal << std::endl;
    }
    std::cout << "Test_SatisfactionCalculator finished" << std::endl;
    
    std::cout << "Starting test TradeCalculator" << std::endl;
    {
        CPrices oPrices;
        CSatisfactionCalculator oSatisfactionCalculator;
        CTradeCalculator oTradeCalculator(&oSatisfactionCalculator, &oPrices);
        std::map<eOpt, double> map_nOption_dAmount;
        for (auto& nOption : c_setOptions)
        {
            map_nOption_dAmount[nOption] = 1.0;
        }
        std::cout << "Probando AdjustBestCombidict..." << std::endl;
        std::map<eOpt, double> mapOpAmmAdjusted = oTradeCalculator.AdjustBestCombidict(10.0, map_nOption_dAmount, 1.0, 100);
        for (auto& pair_Op_Am : mapOpAmmAdjusted)
        {
            std::cout << "Option: " << pair_Op_Am.first << std::endl;
            std::cout << "Amount: " << pair_Op_Am.second << std::endl;
        }
    }
    std::cout << "Test TradeCalculator finished" << std::endl;


    std::cout << "TODO test Market" << std::endl;
    std::cout << "Starting test Market" << std::endl;
    {
        CMarket oMarket;
        CPrices oPrices;
        CSatisfactionCalculator oSatisfactionCalculator_1;        
        CTradeCalculator oTradeCalculator_1(&oSatisfactionCalculator_1, &oPrices);
        CSatisfactionCalculator oSatisfactionCalculator_2;
        CTradeCalculator oTradeCalculator_2(&oSatisfactionCalculator_2, &oPrices);
        CSatisfactionCalculator oSatisfactionCalculator_3;
        CTradeCalculator oTradeCalculator_3(&oSatisfactionCalculator_3, &oPrices);

        CPerson oPerson_1(&oPrices, &oMarket, &oTradeCalculator_1);
        CPerson oPerson_2(&oPrices, &oMarket, &oTradeCalculator_2);
        CPerson oPerson_3(&oPrices, &oMarket, &oTradeCalculator_3);

        std::map<eProd, double> mapProd_Amm;
        for (auto& nProd : c_setProducts)
        {
            oPerson_1.AddProductAmount(nProd, 1.0);
            oPerson_2.AddProductAmount(nProd, 1.0);
            oPerson_3.AddProductAmount(nProd, 1.0);
        }

        oMarket.AddPersonRef(&oPerson_1);
        oMarket.AddPersonRef(&oPerson_2);
        oMarket.AddPersonRef(&oPerson_3);
        double dStep = 1.0;
        double dMaxNumSteps = 10;

        CUtils::PrintPersonOptions(&oPerson_1);
        CUtils::PrintPersonOptions(&oPerson_2);
        CUtils::PrintPersonOptions(&oPerson_3);

        oMarket.AdjustBestCombinations(dStep, dMaxNumSteps);

        CUtils::PrintPersonOptions(&oPerson_1);
        CUtils::PrintPersonOptions(&oPerson_2);
        CUtils::PrintPersonOptions(&oPerson_3);


    }
    std::cout << "Test Market finished" << std::endl;

    return 0;
}

