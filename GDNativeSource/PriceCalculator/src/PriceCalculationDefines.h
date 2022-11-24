#include <set>

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


const std::set<int> c_setOptions = {
c_nOptCandySavings,
c_nOptChocolateSavings,
c_nOptNutSavings,
c_nOptCandyConsumption,
c_nOptChocolateConsumption,
c_nOptNutConsumption
};

const std::set<int> c_setSavings = {
c_nOptCandySavings,
c_nOptChocolateSavings,
c_nOptNutSavings
};

const std::set<int> c_setConsumption = {
c_nOptCandyConsumption,
c_nOptChocolateConsumption,
c_nOptNutConsumption
};
