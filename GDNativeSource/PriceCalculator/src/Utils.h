#ifndef UTILS_H
#define UTILS_H

#include "PriceCalculationDefines.h"

namespace pca
{
    class CUtils
    {
    public:
        CUtils();
        virtual ~CUtils();

        static void PrintOptions(std::map<eOpt, double> mapOpt_Amount);

    protected:

    private:
    };
}

#endif // UTILS_H
