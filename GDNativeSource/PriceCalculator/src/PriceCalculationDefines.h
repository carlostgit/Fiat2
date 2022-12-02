#include <set>
#include <map>

const int c_nOptCandy = 1;
const int c_nOptChocolate = 2;
const int c_nOptNut = 3;

const int c_nOptTypSavings = 1;
const int c_nOptTypConsumption = 2;

const int c_nOptCandySavings = 1;
const int c_nOptChocolateSavings = 2;
const int c_nOptNutSavings = 3;
const int c_nOptCandyConsumption = 4;
const int c_nOptChocolateConsumption = 5;
const int c_nOptNutConsumption = 6;

const int c_nCompCombSweets = 1;

const int c_nSuppCombConsumption = 1;
const int c_nSuppCombSavings = 2;


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


