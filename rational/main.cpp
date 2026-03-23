#include <iostream>
#include "rational.h"

using namespace std;

int main()
{
    Rational a(2, 2);
    Rational b(3, 4);

    Rational c = a * b;

    cout << "a * b = " << c.operator double() << endl;

    a *= b;
    cout << "После a *= b: " << a.operator double() << endl;

    return 0;
}
