#include "calc.h"

#define FLOATING_POINT_APPROX_ZERO 0.00001

double hypotenuse(const int a, const int b) {
    return sqrt(a * a + b * b);
}

// limit var to a range low -- high
int limit(const int val, const int low, const int high) {
    if (val > high)
        return high;
    else if (val < low)
        return low;
    else
        return val;
}

// limit var to a range low -- high
double flimit(const double val, const double low, const double high) {
    if (val > high)
        return high;
    else if (val < low)
        return low;
    else
        return val;
}

// change a range of var from low1 -- high1 to low2 -- high2
int map(const int var, const int low1, const int high1, const int low2, const int high2) {
    int d1 = high1 - low1, d2 = high2 - low2, res = 0;
    
    if (d2 >= d1)
        res = low2 + (var - low1) * (d2 / d1);
    else
        res = low2 + (var - low1) / (d1 / d2);
    
    return limit(res, low2, high2);
}

// change range of var from low1 -- high1 to low2 -- high2
double fmap(const double var, const double low1, const double high1, const double low2, const double high2) {
    double d1 = high1 - low1, d2 = high2 - low2, res = 0.0;
    res = low2 + (var - low1) * (d2 / d1);
    
    return flimit(res, low2, high2);
}

// prevent zero division
double prevent_zero_div(const double a, const double b, const double default_val) {
    if (fabs(b) < FLOATING_POINT_APPROX_ZERO)
        return default_val;
    else
        return a / b;
}