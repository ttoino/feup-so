#include <math.h>
#include <stdlib.h>

#include "vector.h"

vector *vector_new(double x, double y, double z) {
    vector *r = (vector *)malloc(sizeof(vector));
    r->x = x;
    r->y = y;
    r->z = z;
    return r;
}

vector *vector_add(vector *a, vector *b) {
    return vector_new(a->x + b->x, a->y + b->y, a->z + b->z);
}

vector *vector_sub(vector *a, vector *b) {
    return vector_new(a->x - b->x, a->y - b->y, a->z - b->z);
}

vector *vector_scale(double a, vector *v) {
    return vector_new(v->x * a, v->y * a, v->z * a);
}

vector *vector_vprod(vector *a, vector *b) {
    return vector_new(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z,
                      a->x * b->y - a->y * b->x);
}

double vector_sprod(vector *a, vector *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

double vector_mod(vector *v) {
    return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}
