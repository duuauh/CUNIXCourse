#include <iostream>

#include "fraction.h"

using namespace std;

int find_lcf(int a, int b) {
    int base = 0;
    (a<b)?base = a : base = b;
    for (int i=base; i>0; i--) {
        if (a%i==0 && b%i==0) {
            return i;
        }
    }
}

fraction operator + (const fraction& a, const fraction& b) {
    int coeff = find_lcf(a.denominator, b.denominator);
    fraction c;
    c.denominator = a.denominator*b.denominator/coeff;
    c.numerator = a.numerator*b.denominator/coeff + a.denominator*b.numerator/coeff;
    return c;
}

fraction operator - (const fraction& a, const fraction& b) {
    int coeff = find_lcf(a.denominator, b.denominator);
    fraction c;
    c.denominator = a.denominator*b.denominator/coeff;
    c.numerator = a.numerator*b.denominator/coeff - a.denominator*b.numerator/coeff;
    return c;
}

fraction operator * (const fraction& a, const fraction& b) {
    fraction c;
    c.denominator = a.denominator*b.denominator;
    c.numerator = a.numerator*b.numerator;
    return c;
}

fraction operator / (const fraction& a, const fraction& b) {
    fraction c;
    if(b.numerator==0){
        cout<<"divisor cannot be zero"<<endl;
        c.numerator = 0; c.denominator = 0;
        return c;
    }
    c.denominator = a.denominator*b.numerator;
    c.numerator = a.numerator*b.denominator;
    return c;
}

ostream & operator << (ostream & os, const fraction& a) {
    os<<"numerator: "<<a.numerator<<" denominator: "<<a.denominator;
    return os;
}

fraction simplification(fraction a) {
    int coeff = find_lcf(a.numerator, a.denominator);
    fraction c;
    c.numerator = a.numerator/coeff;
    c.denominator = a.denominator/coeff;
    return c;
}

float to_float(fraction a) {
    float c;
    c = (float)(a.numerator)/(float)(a.denominator);
    return c;
}