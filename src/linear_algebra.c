#include "linear_algebra.h"

double vec2_len(const Vec2 u) { return sqrt(u.x * u.x + u.y * u.y); }

DVec2 vec2_normalize(const Vec2 u) {
    return (DVec2) {
        prevent_zero_div(u.x, fabs(u.x), 0),
        prevent_zero_div(u.y, fabs(u.y), 0)
    };
}

Vec2 dvec2_mult_n(const DVec2 u, const double n) { return (Vec2) {u.x * n, u.y * n}; }

Vec2 vec2_limit(const Vec2 u, const Vec2 min, const Vec2 max) {
    return (Vec2) {
        flimit(u.x, min.x, max.x),
        flimit(u.y, min.y, max.y)
    };
}

Vec2 vec2_add(const Vec2 u, const Vec2 v) { return (Vec2) {u.x + v.x, u.y + v.y}; }

Vec2 vec2_sub(const Vec2 u, const Vec2 v) { return (Vec2) {u.x - v.x, u.y - v.y}; }

Vec2 vec2_mult_n(const Vec2 u, const double n) { return (Vec2) {u.x * n, u.y * n}; }

Vec2 vec2_mult_matrix(const Vec2 u, const Mat22 m) {
    return (Vec2) {
        u.x * m.i.x + u.y * m.j.x,
        u.x * m.i.y + u.y * m.j.y
    };
}

Mat22 mat22_mult_n(const Mat22 m, const double n) {
    return (Mat22) {
        vec2_mult_n(m.i, n),
        vec2_mult_n(m.j, n)
    };
}