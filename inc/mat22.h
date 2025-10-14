#pragma once

#include "vec2.h"

typedef struct
{
    double a; double b;
    double c; double d;
} Mat22;

Vec2 vec2_mult_matrix(const Vec2 u, const Mat22 m);