#include <set>
#include <map>

namespace pca
{


    const int c_nProdCandy = 1;
    const int c_nProdChocolate = 2;
    const int c_nProdNut = 3;

    const int c_nOptTypSavings = 4;
    const int c_nOptTypConsumption = 5;

    const int c_nOptCandySavings = 6;
    const int c_nOptChocolateSavings = 7;
    const int c_nOptNutSavings = 8;
    const int c_nOptCandyConsumption = 9;
    const int c_nOptChocolateConsumption = 10;
    const int c_nOptNutConsumption = 11;

    const int c_nCompCombSweets = 12;

    const int c_nSuppCombConsumption = 13;
    const int c_nSuppCombSavings = 14;


    const std::set<int> c_setProducts = {
    c_nProdCandy,
    c_nProdChocolate,
    c_nProdNut
    };

    const std::map<int, std::set<int> > c_mapProduct_setOptions = {
    {c_nProdCandy,{c_nOptCandySavings,c_nOptCandyConsumption}},
    {c_nProdChocolate,{c_nOptChocolateSavings,c_nOptChocolateConsumption}},
    {c_nProdNut,{c_nOptNutSavings,c_nOptNutConsumption}},
    };

    //Esto debería sacarse a partir de lo anterior
    const std::map<int, int > c_mapOption_Product = {

    {c_nOptCandySavings,c_nProdCandy},
    {c_nOptChocolateSavings,c_nProdChocolate},
    {c_nOptNutSavings,c_nProdNut},
    {c_nOptCandyConsumption,c_nProdCandy},
    {c_nOptChocolateConsumption,c_nProdChocolate},
    {c_nOptNutConsumption,c_nProdNut }

    };


    const std::set<int> c_setOptions = {
    c_nOptCandySavings,
    c_nOptChocolateSavings,
    c_nOptNutSavings,
    c_nOptCandyConsumption,
    c_nOptChocolateConsumption,
    c_nOptNutConsumption
    };

    const std::set<int> c_setGroupSavings = {
    c_nOptCandySavings,
    c_nOptChocolateSavings,
    c_nOptNutSavings
    };

    const std::set<int> c_setGroupConsumption = {
    c_nOptCandyConsumption,
    c_nOptChocolateConsumption,
    c_nOptNutConsumption
    };

    const std::set<int> c_setGroupSweets = {
    c_nOptCandyConsumption,
    c_nOptChocolateConsumption,
    };

    const std::map<int, std::set<int> > c_mapComplementaryCombo_setOptions = {
        {c_nCompCombSweets, c_setGroupSweets}
    };

    const std::map<int, std::set<int> > c_mapSupplementaryCombo_setOptions = {
        {c_nSuppCombConsumption, c_setGroupConsumption},
        {c_nSuppCombSavings, c_setGroupSavings}
    };

}
