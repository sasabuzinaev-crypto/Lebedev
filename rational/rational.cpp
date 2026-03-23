#include "rational.h"
#include <cstdlib>

Rational::Rational() : numer(0), denom(1) {}

Rational::Rational(int number) : numer(number), denom(1) {}

Rational::Rational(int n, int d) : numer(n), denom(d)
{
    simplify();
}

void Rational::simplify()
{
    if (denom < 0)
    {
        numer = -numer;
        denom = -denom;
    }

    for (int i = 2; i <= abs(numer) && i <= abs(denom); ++i)
    {
        if (numer % i == 0 && denom % i == 0)
        {
            numer /= i;
            denom /= i;
            --i;
        }
    }
}

Rational& Rational::operator*=(const Rational& r)
{
    numer *= r.numer;
    denom *= r.denom;
    simplify();
    return *this;
}

Rational Rational::operator*(const Rational& r) const
{
    Rational result(*this);
    return result *= r;
}
Rational::operator double() const
{
    return (double)numer / denom;
}
