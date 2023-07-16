#ifndef UTILS_H
#define UTILS_H

#include "PriceCalculationDefines.h"

namespace pca
{
    class CPerson;

    class CUtils
    {
    public:
        CUtils();
        virtual ~CUtils();

        static void PrintOptions(std::map<eOpt, double> mapOpt_Amount);

        static void PrintPersonOptions(CPerson* pPerson);

    protected:

    private:
    };
}

#endif // UTILS_H
