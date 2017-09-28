//Created by: Matthew Rutan
//Date: 10/15/2016
//Rational Number Class implementation

#include "rational.h"
#include <iostream>
#include <cmath>

using namespace std;

//Note:I used 'this' throughout so it is easier to see which numerator or
//denominator is being operated on or accessed

//Returns GCD of a and b
int computeGcd(int a, int b)
{
    if(a == 0){
        return b;
    }

    return computeGcd(b%a, a);
}

//Constructors
//No argument constructor
RationalNumber::RationalNumber(){
    numerator=0;
    denominator=1;
}

//Single argument constructor
RationalNumber::RationalNumber(int a){
    numerator=a;
    denominator=1;
}

//2 argument constructor
//denominator is set to 1 if argument b is 0
RationalNumber::RationalNumber(int a, int b){
    if (b == 0){
        numerator=a;
        denominator=1;
    }else if(a != 0){
        int gcd=computeGcd(abs(a), abs(b));
        if (b < 0){
            numerator=(a/gcd)*-1;
            denominator=(b/gcd)*-1;
        }else{
            numerator=a/gcd;
            denominator=b/gcd;
        }
    }else{
        numerator=a;
        denominator=b;
    }
}

//Primary Functions

//Sets this to a new instance of rational num. with
//top of a and bottom of b.
void RationalNumber::setNum(int a, int b){
    RationalNumber r(a,b);
    *this=r;
}

//Prints the calling rational number
//undefined if denominator == 0
void RationalNumber::print(){
    if (denominator == 0){
        cout << "undefined";
    }else if (numerator != 0){
        cout << numerator << "/" << denominator;
    }else{
        cout << numerator;
    }
}

//addition
RationalNumber RationalNumber::add(RationalNumber &other){
    if(other.denominator != this->denominator){
        int newTop=(this->denominator*other.numerator)+(this->numerator*other.denominator);
        int newBottom=this->denominator*other.denominator;

        RationalNumber r(newTop,newBottom);

        return r;
    }else{
        RationalNumber r(this->numerator+other.numerator,other.denominator);
        return r;
    }
}

//subtraction of rational numbers
RationalNumber RationalNumber::sub(RationalNumber &other){
    if(other.denominator != this->denominator){
        int newTop=(this->numerator*other.denominator)-(this->denominator*other.numerator);
        int newBottom=this->denominator*other.denominator;
        RationalNumber r(newTop,newBottom);

        return r;
    }else{
        RationalNumber r(this->numerator-other.numerator,other.denominator);

        return r;
    }
}

//multiplication of rational numbers
RationalNumber RationalNumber::mult(RationalNumber &other){
    int newTop=this->numerator*other.numerator;
    int newBottom=this->denominator*other.denominator;

    RationalNumber r(newTop,newBottom);

    return r;
}

//division of rational numbers
//if there is division by 0 (n/0), the rational number will
//be changed to (n/1).
RationalNumber RationalNumber::div(RationalNumber &other){
    int newTop=this->numerator*other.denominator;
    int newBottom=this->denominator*other.numerator;

    RationalNumber r(newTop,newBottom);

    return r;
}

//returns the double result of a Rational Number divided by a double.
double RationalNumber::div(double num){
    double r=(this->numerator)/(this->denominator*num);

    return r;
}

//boolean value of this<other
bool RationalNumber::lessThan(RationalNumber &other){
    bool lessThan=false;

    if(this->numerator*other.denominator < this->denominator*other.numerator){
        lessThan=true;
    }

    return lessThan;
}

//negate rational number
RationalNumber RationalNumber::negateNum(){
    RationalNumber r(this->numerator*-1,this->denominator);
    return r;
}

/*Operator overloading: The RationalNumber add,subtract,div,mult,lessThan, and negateNum functions
were used in the operating overloading functions. Reusing the same code from
the functions listed above seems redundant and unnecessary. This solution would
also make changing the functions easier, as code would only need to be changed
in on location for each function.*/

//adds this and other and returns a new instance of Rational Number
//with the result.
RationalNumber RationalNumber::operator+(RationalNumber &other){
    return this->add(other);
}

//subtracts this and other and returns a new instance of Rational Number
//with the result.
RationalNumber RationalNumber::operator-(RationalNumber &other){
    return this->sub(other);
}

//multiplies this and other and returns a new instance of Rational Number
//with the result.
RationalNumber RationalNumber::operator*(RationalNumber &other){
    return this->mult(other);
}

//divides this and other and returns a new instance of Rational Number
//with the result.
RationalNumber RationalNumber::operator/(RationalNumber &other){
    return this->div(other);
}

//returns the double result of a Rational Number divided by a double.
double RationalNumber::operator/(double num){
    return this->div(num);
}

//compares this and other and returns the logical result
bool RationalNumber::operator<(RationalNumber &other){
    return this->lessThan(other);
}

//returns negative of rational number
RationalNumber RationalNumber::operator-(){
    return this->negateNum();
}
