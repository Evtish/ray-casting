#pragma once

#include "calc.h"

typedef struct {
    double x;
    double y;
} Vec2;

typedef struct {
    int x;
    int y;
} DVec2;

typedef struct
{
    Vec2 i; // 1st *row*
    Vec2 j; // 2nd *row*
} Mat22;

double vec2_len(const Vec2 u);
DVec2 vec2_normalize(const Vec2 u);
Vec2 dvec2_mult_n(const DVec2 u, const double n);
Vec2 vec2_limit(const Vec2 u, const Vec2 min, const Vec2 max);
Vec2 vec2_add(const Vec2 u, const Vec2 v);
Vec2 vec2_sub(const Vec2 u, const Vec2 v);
Vec2 vec2_mult_n(const Vec2 u, const double n);
Vec2 vec2_mult_matrix(const Vec2 u, const Mat22 m);

Mat22 mat22_mult_n(const Mat22 m, const double n);