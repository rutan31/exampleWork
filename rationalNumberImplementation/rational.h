//Created by: Matthew Rutan
//Date: 10/15/2016
//Header for RationalNumber Class

#ifndef RATIONAL_H_INCLUDED
#define RATIONAL_H_INCLUDED

class RationalNumber{
private:
    int numerator;
    int denominator;

public:
    RationalNumber();
    RationalNumber(int a);
    RationalNumber(int a, int b);
    void setNum(int a, int b);
    void print();

    RationalNumber add(RationalNumber&);
    RationalNumber sub(RationalNumber&);
    RationalNumber div(RationalNumber&);
    double div(double num);

    RationalNumber mult(RationalNumber&);
    RationalNumber operator+(RationalNumber&);
    RationalNumber operator-(RationalNumber&);
    RationalNumber operator/(RationalNumber&);
    RationalNumber operator*(RationalNumber&);
    bool lessThan(RationalNumber&);
    bool operator<(RationalNumber &other);
    RationalNumber negateNum();
    double operator/(double num);
    RationalNumber operator-();
};

#endif // RATIONAL_H_INCLUDED
