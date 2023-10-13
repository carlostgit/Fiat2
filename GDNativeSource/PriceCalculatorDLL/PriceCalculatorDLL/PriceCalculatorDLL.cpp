#include "pch.h"
#include "PriceCalculatorDLL.h"

//includes para las llamadas a PriceCalculator
#include "../../PriceCalculator/src/PriceCalculator.h"
#include "../../PriceCalculator/src/PriceCalculatorStaticUser.h"
#include "../../PriceCalculator/src/Tester.h"

long GetTestPriceFromDLL()
{
	//TODO
	//Desde aquí llamar a algún método de PriceCalculator.h

	//LLamada de prueba a Tester de PriceCalculator
	int Test_SatisfactionCurve();

	return 7;
}

long GetTestPriceFromDLL2(long nArg)
{
	//TODO
	//Desde aquí llamar a algún método de PriceCalculator.h

	long nTestPrice = pca::CPriceCalculator::GetTestPrice();

	return 7 + nArg + nTestPrice;
}

void CreateEmptyMarketFromDLL()
{
	pca::CPriceCalculatorStaticUser::CreateEmptyMarket();
}
