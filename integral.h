
//Main for "integral" C application
//Created by r4m0nl1m4 14/10/2020

//Guard
#ifndef INTEGRAL_H
#define INTEGRAL_H

double f(double x){ return -x*x+2*x+2; }

double getTrapezoidRuleBySerie(double n, double a, double h){
    double x_i, b, areaTotal;
    b = a + n*h;
    areaTotal = (f(a)+f(b))/2;
    for ( int i=1; i<n; i++ ){
        x_i = a+i*h;
        areaTotal += f(x_i);
    }
    areaTotal = h*areaTotal;
    return areaTotal;
}

#endif