#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

using namespace std;

class Rational {
private:

public:
    int num;
    int denom;
    
    Rational();
    Rational(int n);
    Rational(int n, int d);

    Rational& operator += (const Rational& other);
    Rational operator + (const Rational& other) const;
    Rational operator -() const;
    Rational operator - (const Rational& other) const;
    Rational& operator -= (const Rational& other);
    Rational& operator ++();
    Rational operator ++(int);
    operator int() const;
    operator double() const;
    Rational& operator *= (const Rational& other);
    Rational operator * (const Rational& other) const;
    Rational& operator /= (const Rational& other);
    Rational operator / (const Rational& other) const;
    bool operator != (const Rational& other) const;
    bool operator < (const Rational& other) const;
    bool operator > (const Rational& other) const;
    bool operator <= (const Rational& other) const;
    bool operator >= (const Rational& other) const; 
    bool operator == (const Rational& other) const;
   
    friend istream& operator>>(istream& inputStream,
                               Rational& value);

    friend ostream& operator<<(ostream& outputStream,
                               const Rational& value);
};


Rational& simplify(Rational& value);

Rational FromDouble(double value,
                    double eps,
                    int maxDenom);

Rational sqrtRational(const Rational& value);

#endif