#include "Tester.h"
#include <iostream>
#include "SatisfactionCurve.h"

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
