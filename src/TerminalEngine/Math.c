#include "Math.h"

const float PI = 3.14159f;

void addV3(Vec3* a, Vec3* b, Vec3* out) {
    out->x = a->x + b->x;
    out->y = a->y + b->y;
    out->z = a->z + b->z;
}

void subV3(Vec3* a, Vec3* b, Vec3* out) {
    out->x = a->x - b->x;
    out->y = a->y - b->y;
    out->z = a->z - b->z;
}

void mulV3(float a, Vec3* v, Vec3* out) {
    out->x = a * v->x;
    out->y = a * v->y;
    out->z = a * v->z;
}

void cross(Vec3* a, Vec3* b, Vec3* c) {
    c->x = a->y * b->z - a->z * b->y;
    c->y = a->z * b->x - a->x * b->z;
    c->z = a->x * b->y - a->y * b->x;
}

float dot(Vec3* a, Vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

void normalize(Vec3* in) {
    float invLen = 1 / sqrtf(dot(in, in));
    in->x *= invLen;
    in->y *= invLen;
    in->z *= invLen;
}

void matXvec(Mat4* matrix, Vec3* in, Vec3* out) {
    // Since we input a 3-dimensional vector, to multiply the matrix by the vector we assume that the vector has
    // a fourth element, w = 1.
    out->x = in->x * matrix->mat[0][0] + in->y * matrix->mat[1][0] + in->z * matrix->mat[2][0] + matrix->mat[3][0];
    out->y = in->x * matrix->mat[0][1] + in->y * matrix->mat[1][1] + in->z * matrix->mat[2][1] + matrix->mat[3][1];
    out->z = in->x * matrix->mat[0][2] + in->y * matrix->mat[1][2] + in->z * matrix->mat[2][2] + matrix->mat[3][2];

    float w = in->x * matrix->mat[0][3] + in->y * matrix->mat[1][3] + in->z * matrix->mat[2][3] + matrix->mat[3][3];

    // We normalize the output vector by the 4th element that gets produced by the matrix vector multiplication.

    if(w != 0) {
        out->x /= w;
        out->y /= w;
        out->z /= w;
    }
}