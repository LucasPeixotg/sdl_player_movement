#include <math.h>
#include <stdio.h>

void normalize_vector2(float vector[2]) {
    float len = sqrt(vector[0]*vector[0] + vector[1]*vector[1]);
    vector[0] = vector[0] / len;
    vector[1] = vector[1] / len;
}