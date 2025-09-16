#pragma once

#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} vec2;

typedef struct {
    int x;
    int y;
} d_vec2;

double vec2_len(const vec2 u);
d_vec2 vec2_normalize(const vec2 u);
vec2 vec2_add(const vec2 u, const vec2 v);
vec2 vec2_sub(const vec2 u, const vec2 v);
vec2 vec2_scalarMult_n(const vec2 u, const double n);
vec2 vec2_scalarMult_vec2(const vec2 u, const vec2 v);
