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

        static std::map<pca::CProduct*, double> SumProducts(const std::map<pca::CProduct*, double> & mapProductAmount_1, const std::map<pca::CProduct*, double> & mapProductAmount_2);
        static std::map<pca::COption*, double> SumOptions(const std::map<pca::COption*, double> & mapOptionAmount_1, const std::map<pca::COption*, double> & mapOptionAmount_2);

        static std::map<pca::CProduct*, double> SubtractProducts(const std::map<pca::CProduct*, double> & mapProductAmount_1, const std::map<pca::CProduct*, double> & mapProductAmount_2);
        static std::map<pca::COption*, double> SubtractOptions(const std::map<pca::COption*, double> & mapOptionAmount_1, const std::map<pca::COption*, double> & mapOptionAmount_2);


    protected:

    private:
    };
}

#endif // UTILS_H
