#pragma once

#include <math.h>

#define arr_len(arr) sizeof arr / sizeof arr[0]

#define ALMOST_INF 1e14 // arbitrary huge number

double hypotenuse(const int a, const int b);
int limit(const int val, const int low, const int high);
double flimit(const double val, const double low, const double high);
int map(const int var, const int low1, const int high1, const int low2, const int high2);
double fmap(const double var, const double low1, const double high1, const double low2, const double high2);
double prevent_zero_div(const double a, const double b, const double default_val);
double correct_gamma(const double val);
