#include "vec2.h"

double vec2_len(const Vec2 u) { return sqrt(u.x * u.x + u.y * u.y); }

Vec2 vec2_normalize(const Vec2 u) {
    double len = vec2_len(u);
    return (Vec2) {
        prevent_zero_div(u.x, len, 0),
        prevent_zero_div(u.y, len, 0),
    };
}

// changes the coordinates of the vector by 1, 0, or -1
DVec2 vec2_quantize(const Vec2 u) {
    return (DVec2) {
        prevent_zero_div(u.x, fabs(u.x), 0),
        prevent_zero_div(u.y, fabs(u.y), 0)
    };
}

Vec2 vec2_limit(const Vec2 u, const Vec2 min, const Vec2 max) {
    return (Vec2) {
        flimit(u.x, min.x, max.x),
        flimit(u.y, min.y, max.y)
    };
}

Vec2 vec2_add(const Vec2 u, const Vec2 v) { return (Vec2) {u.x + v.x, u.y + v.y}; }

Vec2 vec2_mult_n(const Vec2 u, const double n) { return (Vec2) {u.x * n, u.y * n}; }