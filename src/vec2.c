#include "vec2.h"

double vec2_len(const Vec2 u) { return sqrt(u.x * u.x + u.y * u.y); }

DVec2 vec2_normalize(const Vec2 u) {
    return (DVec2) {
        prevent_zero_div(u.x, fabs(u.x), 0),
        prevent_zero_div(u.y, fabs(u.y), 0)
    };
}

Vec2 vec2_add(const Vec2 u, const Vec2 v) { return (Vec2) {u.x + v.x, u.y + v.y}; }

Vec2 vec2_sub(const Vec2 u, const Vec2 v) { return (Vec2) {u.x - v.x, u.y - v.y}; }

Vec2 vec2_scalar_mult_n(const Vec2 u, const double n) { return (Vec2) {u.x * n, u.y * n}; }
