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

double vec2_len(const Vec2 u);
DVec2 vec2_normalize(const Vec2 u);
Vec2 vec2_add(const Vec2 u, const Vec2 v);
Vec2 vec2_sub(const Vec2 u, const Vec2 v);
Vec2 vec2_scalar_mult_n(const Vec2 u, const double n);
