#include "MarketTest.h"

extern "C" double calculationTest(int i)
{
    double dI = static_cast<double>(i);
    dI += 1.5;

    return dI;
}
