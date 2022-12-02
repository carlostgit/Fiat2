#include <iostream>
#include "Tester.h"

using namespace std;

int main()
{
    CTester oTester;

    oTester.Test_SatisfactionCurve();

    oTester.Test_SatisfactionCalculator();

    cout << "Hello world!" << endl;
    return 0;
}
