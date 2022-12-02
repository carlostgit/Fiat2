#include "Tester.h"
#include <iostream>
#include "PriceCalculationDefines.h"
#include "SatisfactionCurve.h"
#include "SatisfactionCalculator.h"


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
    double dSatisf = oSatCalculator.CalculateSatisfOfCombidictFromIndividualOptions(map_nOption_dAmount);
    std::cout << "dSatisfAt_"<<": "<< dSatisf << std::endl;
    //Esto hay que inicializarlo primero bien

    //TODO... hacer el test de Test_SatisfactionCalculator
    std::cout << "TODO... hacer el test de Test_SatisfactionCalculator" << std::endl;

    std::cout << "Test_SatisfactionCalculator finished" << std::endl;
}

