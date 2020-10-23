#include <iostream>

using namespace std;

typedef struct faction{
    int numerator;
    int denominator;
} fraction;

int find_lcf(int a, int b);
fraction operator + (const fraction& a, const fraction& b);
fraction operator - (const fraction& a, const fraction& b);
fraction operator * (const fraction& a, const fraction& b);
fraction operator / (const fraction& a, const fraction& b);
ostream & operator << (ostream & os, const fraction& a);
fraction simplification(fraction a);
float to_float(fraction a);