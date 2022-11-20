#ifndef CSATISFACTIONCURVE_H
#define CSATISFACTIONCURVE_H


class CSatisfactionCurve
{
    public:
        CSatisfactionCurve();
        virtual ~CSatisfactionCurve();

        double GetDiminishingReturnsFactor(double dQuantity);
        double CalculateSatifaction(double dQuantity);

    protected:

    private:
        double m_dPreferenceAt0 = 2.16;
        double m_dMaximumSatisf = 10.0;
};

#endif // CSATISFACTIONCURVE_H
