#ifndef CPRICECALCULATIONDEFINES_H
#define CPRICECALCULATIONDEFINES_H


#include <set>
#include <map>


namespace pca
{

    //TODO. Cambiar esto por enumeradores. O crear clases (Clase CProduct etc...)

    enum eProd {
        eProdCandy = 1,
        eProdChocolate = 2,
        eProdNut = 3,
    };
    //const int c_nProdCandy = 1;
    //const int c_nProdChocolate = 2;
    //const int c_nProdNut = 3;

    enum eOptTyp {
        eOptTypSavings = 4,
        eOptTypConsumption = 5
    };

    //const int eOptTypSavings = 4;
    //const int eOptTypConsumption = 5;
    
    enum eOpt {
        eOptCandySavings = 6,
        eOptChocolateSavings = 7,
        eOptNutSavings = 8,
        eOptCandyConsumption = 9,
        eOptChocolateConsumption = 10,
        eOptNutConsumption = 11
    };

    //const int eOptCandySavings = 6;
    //const int eOptChocolateSavings = 7;
    //const int eOptNutSavings = 8;
    //const int eOptCandyConsumption = 9;
    //const int eOptChocolateConsumption = 10;
    //const int eOptNutConsumption = 11;
    
    enum eCompComb {
        eCompCombSweets = 12
    };

    //const int c_nCompCombSweets = 12;

    enum eSuppComb {
        c_nSuppCombConsumption = 13,
        c_nSuppCombSavings = 14
    };

    //const int c_nSuppCombConsumption = 13;
    //const int c_nSuppCombSavings = 14;


    const std::set<pca::eProd> c_setProducts = {
    eProdCandy,
    eProdChocolate,
    eProdNut
    };

    const std::map<pca::eProd, std::set<pca::eOpt> > c_mapProduct_setOptions = {
    {eProdCandy,{eOptCandySavings,eOptCandyConsumption}},
    {eProdChocolate,{eOptChocolateSavings,eOptChocolateConsumption}},
    {eProdNut,{eOptNutSavings,eOptNutConsumption}},
    };

    //Esto debería sacarse a partir de lo anterior
    const std::map<pca::eOpt, pca::eProd > c_mapOption_Product = {

    {eOptCandySavings,eProdCandy},
    {eOptChocolateSavings,eProdChocolate},
    {eOptNutSavings,eProdNut},
    {eOptCandyConsumption,eProdCandy},
    {eOptChocolateConsumption,eProdChocolate},
    {eOptNutConsumption,eProdNut }

    };


    const std::set<pca::eOpt> c_setOptions = {
    eOptCandySavings,
    eOptChocolateSavings,
    eOptNutSavings,
    eOptCandyConsumption,
    eOptChocolateConsumption,
    eOptNutConsumption
    };

    const std::set<pca::eOpt> c_setGroupSavings = {
    eOptCandySavings,
    eOptChocolateSavings,
    eOptNutSavings
    };

    const std::set<pca::eOpt> c_setGroupConsumption = {
    eOptCandyConsumption,
    eOptChocolateConsumption,
    eOptNutConsumption
    };

    const std::set<pca::eOpt> c_setGroupSweets = {
    eOptCandyConsumption,
    eOptChocolateConsumption,
    };

    const std::map<pca::eCompComb, std::set<pca::eOpt> > c_mapComplementaryCombo_setOptions = {
        {eCompCombSweets, c_setGroupSweets}
    };

    const std::map<pca::eSuppComb, std::set<pca::eOpt> > c_mapSupplementaryCombo_setOptions = {
        {c_nSuppCombConsumption, c_setGroupConsumption},
        {c_nSuppCombSavings, c_setGroupSavings}
    };

}

#endif //CPRICECALCULATIONDEFINES_H