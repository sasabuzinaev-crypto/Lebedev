#include <iostream>
#include "rational.h"

using namespace std;

void solveQuadratic(const Rational& coefA,
                    const Rational& coefB,
                    const Rational& coefC)
{
    if (coefA.num == 0) {

        if (coefB.num == 0) {
            cout << "Нет решения\n";
            return;
        }

        double root =
            - (double)coefC.num / coefC.denom /
            ((double)coefB.num / coefB.denom);

        cout << "x = " << root << "\n";
        return;
    }

    Rational constFour(4,1);
    Rational constTwo(2,1);

    Rational discriminant =
        coefB * coefB - constFour * coefA * coefC;

    if (discriminant.num < 0) {
        cout << "Нет вещественных рациональных корней\n";
        return;
    }

    try {

        Rational sqrtD = sqrtRational(discriminant);

        Rational root1 =
            (-coefB + sqrtD) / (-coefA * constTwo);

        Rational root2 =
            (-coefB - sqrtD) / (-coefA * constTwo);

        cout << "x1 = " << root1
             << ", x2 = " << root2 << "\n";

    } catch (...) {
        cout << "Ошибка вычисления корня\n";
    }
}

int main()
{
    Rational coefA, coefB, coefC;

    cout << "a (num denom): ";
    cin >> coefA.num >> coefA.denom;

    cout << "b (num denom): ";
    cin >> coefB.num >> coefB.denom;

    cout << "c (num denom): ";
    cin >> coefC.num >> coefC.denom;

    coefA = Rational(coefA.num, coefA.denom);
    coefB = Rational(coefB.num, coefB.denom);
    coefC = Rational(coefC.num, coefC.denom);

    cout << "\n--- Тестирование ---\n";

    Rational sumRes = coefA + coefB;
    cout << "a + b = " << sumRes << "\n";

    Rational diffRes = coefA - coefB;
    cout << "a - b = " << diffRes << "\n";

    Rational mulRes = coefA * coefB;
    cout << "a * b = " << mulRes << "\n";

    Rational divRes = coefA / coefB;
    cout << "a / b = " << divRes << "\n";

    Rational negRes = -coefA;
    cout << "-a = " << negRes << "\n";

    cout << "a == b ? "
         << (coefA == coefB ? "true" : "false") << "\n";

    Rational testFrac(8,12);
    simplify(testFrac);

    cout << "8/12 simplified = "
         << testFrac << "\n";

    Rational fromDoubleRes =
        FromDouble(0.75, 1e-6, 1000);

    cout << "FromDouble = "
         << fromDoubleRes << "\n";

    solveQuadratic(coefA, coefB, coefC);
}