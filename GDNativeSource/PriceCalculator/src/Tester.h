#ifndef TESTER_H
#define TESTER_H

namespace pca
{
    class CTester
    {
    public:
        CTester();
        virtual ~CTester();

        int Test_SatisfactionCurve();
        int Test_SatisfactionCalculator();

    protected:

    private:
    };
}

#endif // TESTER_H
