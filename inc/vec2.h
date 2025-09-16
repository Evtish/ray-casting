#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} vec2;

double vec2Len(vec2 u);
vec2 vec2Normalize(vec2 u);
vec2 vec2Add(vec2 u, vec2 v);
vec2 vec2Sub(vec2 u, vec2 v);
vec2 vec2ScalarMult(vec2 u, vec2 v);
