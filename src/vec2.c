#include "vec2.h"

double vec2Len(vec2 u) { return sqrt(u.x * u.x + u.y * u.y); }
vec2 vec2Normalize(vec2 u) { return (vec2) {u.x / fabs(u.x), u.y / fabs(u.y)}; }
vec2 vec2Add(vec2 u, vec2 v) { return (vec2) {u.x + v.x, u.y + v.y}; }
vec2 vec2Sub(vec2 u, vec2 v) { return (vec2) {u.x - v.x, u.y - v.y}; }
vec2 vec2ScalarMult(vec2 u, vec2 v) { return (vec2) {u.x * v.x, u.y * v.y}; }
