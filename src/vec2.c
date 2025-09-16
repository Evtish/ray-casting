#include "vec2.h"

double vec2_len(const vec2 u) { return sqrt(u.x * u.x + u.y * u.y); }

d_vec2 vec2_normalize(const vec2 u) {
    int x = (fabs(u.x) < 0.0001) ? 0 : u.x / fabs(u.x);
    int y = (fabs(u.y) < 0.0001) ? 0 : u.y / fabs(u.y);
    return (d_vec2) {x, y};
}

vec2 vec2_add(const vec2 u, const vec2 v) { return (vec2) {u.x + v.x, u.y + v.y}; }

vec2 vec2_sub(const vec2 u, const vec2 v) { return (vec2) {u.x - v.x, u.y - v.y}; }

vec2 vec2_scalarMult_n(const vec2 u, const double n) { return (vec2) {u.x * n, u.y * n}; }

vec2 vec2_scalarMult_vec2(const vec2 u, const vec2 v) { return (vec2) {u.x * v.x, u.y * v.y}; }
