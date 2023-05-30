#ifndef CSATISFACTIONCURVE_H
#define CSATISFACTIONCURVE_H

namespace pca
{
    class CSatisfactionCurve
    {
    public:
        CSatisfactionCurve();
        virtual ~CSatisfactionCurve();

        double CalculateSatifaction(double dQuantity);

        void SetPreferenceAt0(double dPreferenceAt0) {
            m_dPreferenceAt0 = dPreferenceAt0;
        };
        double GetPreferenceAt0() {
            return m_dPreferenceAt0;
        };

        void SetMaximumSatisf(double dMaximumSatisf) {
            m_dMaximumSatisf = dMaximumSatisf;
        };
        double GetMaximumSatisf() {
            return m_dMaximumSatisf;
        };


    protected:
        double GetDiminishingReturnsFactor(double dQuantity);

    private:
        double m_dPreferenceAt0 = 2.16;
        double m_dMaximumSatisf = 10.0;
    };

}

#endif // CSATISFACTIONCURVE_H
