#include "SatisfactionCurve.h"

CSatisfactionCurve::CSatisfactionCurve()
{
    //ctor
}

CSatisfactionCurve::~CSatisfactionCurve()
{
    //dtor
}


double CSatisfactionCurve::GetDiminishingReturnsFactor(double dQuantity)
{
    //#Voy a llamar al termino "1-(1/(x+1))" Diminishing Returns Factor
    //#Esta ecuaci�n tendr�a un m�ximo en 1, y tendr�a pendiente 1 en 0
    //#Es como una ecuaci�n y = x, pero que se va haciendo m�s y m�s horizontal hasta q ya no crece la y

	double dResult = 0.0;
	double dDenominator = dQuantity+1.0;

	dResult = 1.0 - (1.0/dDenominator);
	if (dResult < 0)
		dResult = 0;

	return dResult;
}

double CSatisfactionCurve::CalculateSatifaction(double dQuantity)
{

	double dRetSatisf = 0.0;
	double dPrefAt0 = m_dPreferenceAt0;
	double dMaxSatisf = m_dMaximumSatisf;

	if (dMaxSatisf==0)
		return dMaxSatisf;

	dRetSatisf = dMaxSatisf*GetDiminishingReturnsFactor(dQuantity*dPrefAt0/dMaxSatisf);

	return dRetSatisf;
}

