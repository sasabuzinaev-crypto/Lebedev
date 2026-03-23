//
//  rational.h
//  умножения
//
//  Created by Александр Бузинаев on 02/03/2026.
//

#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{
private:
    int numer;
    int denom;

    void simplify();

public:
    operator double() const;
    Rational();
    Rational(int number);
    Rational(int n, int d);

    Rational operator*(const Rational& r) const;
    Rational& operator*=(const Rational& r);
};

#endif
