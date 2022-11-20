#ifndef CPRICECALCULATOR_H
#define CPRICECALCULATOR_H

#include <vector>
#include <memory>


class CPerson;
class CPrices;

class CPriceCalculator
{
    public:
        CPriceCalculator();
        virtual ~CPriceCalculator();


    protected:

    private:
        //Usar unique_ptr aquí requiere que las clases se incluyan en el cpp
        //para que el compilador sepa cómo destruir sus objetos

        std::vector<std::unique_ptr<CPerson> > m_vpPersons;
        std::unique_ptr<CPrices> m_pPrices;

};

#endif // CPRICECALCULATOR_H
