#include "Tester.h"
#include <iostream>
#include "PriceCalculationDefines.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"
#include "TradeCalculator.h"


CTester::CTester()
{
    //ctor

    std::cout << "Creating CTester" << std::endl;
}

CTester::~CTester()
{
    //dtor
}

CTester::Test_SatisfactionCurve()
{
    std::cout << "Starting Test_SatisfactionCurve" << std::endl;

    CSatisfactionCurve oSatCurve;

    for (int i=0; i<20; i++)
    {
        double dSatisf = oSatCurve.CalculateSatifaction(i);
        std::cout << "dSatisfAt_"<<i << ": "<< dSatisf << std::endl;
    }

    std::cout << "Test_SatisfactionCurve finished" << std::endl;
}

CTester::Test_SatisfactionCalculator()
{
    std::cout << "Starting Test_SatisfactionCalculator" << std::endl;

    CSatisfactionCalculator oSatCalculator;
    std::map<int,double> map_nOption_dAmount;
    for(auto & nOption:c_setOptions)
    {
        map_nOption_dAmount[nOption] = 1.0;

    }
    std::cout << "Prueba..." << std::endl;
    double dSatisfFormIndivOptions = oSatCalculator.CalculateSatisfOfCombidictFromIndividualOptions(map_nOption_dAmount);
    std::cout << "dSatisfFormIndivOptions: "<< dSatisfFormIndivOptions << std::endl;
    double dSatisfFormSuppCombos = oSatCalculator.CalculateSatisfOfCombidictFromSupplementaryCombos(map_nOption_dAmount);
    std::cout << "dSatisfFormSuppCombos "<< dSatisfFormSuppCombos << std::endl;
    double dSatisfFormCompCombos = oSatCalculator.CalculateSatisfOfCombidictFromComplementaryCombos(map_nOption_dAmount);
    std::cout << "dSatisfFormCompCombos "<< dSatisfFormCompCombos << std::endl;
    double dSatisfTotal = oSatCalculator.CalculateSatisfOfCombidict(map_nOption_dAmount);
    std::cout << "dSatisfTotal "<< dSatisfTotal << std::endl;


    //TODO... hacer el test de Test_SatisfactionCalculator
    std::cout << "TODO... hacer el test de Test_SatisfactionCalculator" << std::endl;

    std::cout << "Test_SatisfactionCalculator finished" << std::endl;
    ;

    CTradeCalculator oTradeCalculator;
    std::cout << "Probando AdjustBestCombidict..." << std::endl;
    std::map<int,double> mapOpAmmAdjusted = oTradeCalculator.AdjustBestCombidict(10.0, map_nOption_dAmount,1.0,100);
    for (auto & pair_Op_Am:mapOpAmmAdjusted)
    {
       std::cout << "Option: "<< pair_Op_Am.first << std::endl;
       std::cout << "Amount: "<< pair_Op_Am.second<< std::endl;
    }

}

