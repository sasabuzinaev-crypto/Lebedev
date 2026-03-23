#include "rational.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

Rational::Rational()
{
    num = 0;
    denom = 1;
}

Rational::Rational(int n)
{
    num = n;
    denom = 1;
}

Rational::Rational(int n, int d)
{
    num = n;
    denom = d;
}

Rational& Rational::operator += (const Rational& other)
{
    num = num * other.denom + denom * other.num;
    denom = denom * other.denom;
    return *this;
}

istream& operator>>(istream& inputStream, Rational& value)
{
    inputStream >> value.num >> value.denom;
    return inputStream;
}

ostream& operator<<(ostream& outputStream, const Rational& value)
{
    outputStream << value.num << "/" << value.denom;
    return outputStream;
}

Rational Rational::operator+(const Rational& other) const
{
    Rational result(*this);
    result += other;
    return result;
}

Rational Rational::operator-() const
{
    Rational temp(-num, denom);
    return temp;
}

Rational Rational::operator-(const Rational& other) const
{
    Rational result(*this);
    result += -other;
    return result;
}

Rational& Rational::operator-=(const Rational& other)
{
    *this += -other;
    return *this;
}

Rational& Rational::operator++()
{
    *this += Rational(1,1);
    return *this;
}

Rational Rational::operator++(int)
{
    Rational result(*this);
    *this += Rational(1,1);
    return result;
}

Rational::operator int() const
{
    return num / denom;
}

Rational::operator double() const
{
    return (double)num / denom;
}

Rational& Rational::operator*=(const Rational& other)
{
    num = num * other.num;
    denom = denom * other.denom;
    return *this;
}

Rational Rational::operator*(const Rational& other) const
{
    Rational result(*this);
    result *= other;
    return result;
}

Rational& Rational::operator/=(const Rational& other)
{
    num = num * other.denom;
    denom = denom * other.num;
    return *this;
}

Rational Rational::operator/(const Rational& other) const
{
    Rational result(*this);
    result /= other;
    return result;
}

bool Rational::operator!=(const Rational& other) const
{
    return num * other.denom != denom * other.num;
}

bool Rational::operator<(const Rational& other) const
{
    return num * other.denom < denom * other.num;
}

bool Rational::operator>(const Rational& other) const
{
    return num * other.denom > denom * other.num;
}

bool Rational::operator<=(const Rational& other) const
{
    return num * other.denom <= denom * other.num;
}

bool Rational::operator>=(const Rational& other) const
{
    return num * other.denom >= denom * other.num;
}

bool Rational::operator==(const Rational& other) const
{
    return num * other.denom == denom * other.num;
}

Rational& simplify(Rational& value)
{
    int a = value.num;
    int b = value.denom;

    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }

    int g = a;

    value.num /= g;
    value.denom /= g;

    if (value.denom < 0) {
        value.denom = -value.denom;
        value.num = -value.num;
    }

    return value;
}

Rational FromDouble(double value, double eps, int maxDenom)
{
    int denom = 1;
    int num = 0;

    while (denom <= maxDenom) {

        num = round(value * denom);

        if (abs(value - (double)num / denom) < eps)
            break;

        denom++;
    }

    Rational result(num, denom);
    simplify(result);
    return result;
}

bool isPerfectSquare(int value)
{
    if (value < 0) return false;

    int root = (int)std::sqrt(value);

    return root * root == value;
}

Rational sqrtRational(const Rational& value)
{
    if (!isPerfectSquare(value.num) ||
        !isPerfectSquare(value.denom))
    {
        throw runtime_error(
            "Дискриминант не является квадратом рационального числа"
        );
    }

    return Rational(
        (int)sqrt(value.num),
        (int)sqrt(value.denom)
    );
}