#ifndef UTILS_H
#define UTILS_H

//#include "PriceCalculationDefines.h"
#include <map>

namespace pca
{
    class CPerson;
    class COption;
    class CProduct;

    class CUtils
    {
    public:
        CUtils();
        virtual ~CUtils();

        static void PrintOptions(std::map<COption*, double> mapOpt_Amount);

        static void PrintPersonOptions(CPerson* pPerson);

        static std::map<pca::CProduct*, double> CalculateProductdictFromOptiondict(std::map<COption*, double> mapOptiondictArg);

    protected:

    private:
    };
}

#endif // UTILS_H
