#include "mat22.h"

Vec2 vec2_mult_matrix(const Vec2 u, const Mat22 m) {
    return (Vec2) {
        u.x * m.a + u.y * m.b,
        u.x * m.c + u.y * m.d
    };
}