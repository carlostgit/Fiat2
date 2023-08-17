#ifndef CPRICECALCULATOR_H
#define CPRICECALCULATOR_H

#include "Market.h"

#include <vector>
#include <memory>



namespace pca
{
    class CPerson;
    class CPrices;
    class CMarket;

    class CPriceCalculator
    {
    public:
        CPriceCalculator();
        virtual ~CPriceCalculator();


        static int GetTestPrice();

    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos

        std::unique_ptr<CMarket> m_upMarket;
        

    };
}

#endif // CPRICECALCULATOR_H
