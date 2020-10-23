#include <iostream>
#include <iomanip>

#include "fraction.h"

using namespace std;

int main() {

    fraction a;
    fraction b;

    int an,ad,bn,bd;
    cout<<"input numerator of a:"<<endl;
    cin>>an;
    cout<<"input denominator of a:"<<endl;
    cin>>ad;
    cout<<"input numerator of b:"<<endl;
    cin>>bn;
    cout<<"input denominator of b:"<<endl;
    cin>>bd;
    a.numerator = an;
    a.denominator = ad;
    b.numerator = bn;
    b.denominator = bd;
    
    cout<<"sum: "<<a+b<<endl;
    cout<<"diff: "<<a-b<<endl;
    cout<<"multi: "<<a*b<<endl;
    cout<<"divid: "<<a/b<<endl;
    cout<<"simplified sum: "<<simplification(a+b)<<endl;
    cout<<"simplified diff: "<<simplification(a-b)<<endl;
    cout<<"simplified multi: "<<simplification(a*b)<<endl;
    cout<<"simplified divid: "<<simplification(a/b)<<endl;
    cout<<"float a: "<<setprecision(5)<<to_float(a)<<endl;
    cout<<"float b: "<<setprecision(5)<<to_float(b)<<endl;

    return 0;
}
