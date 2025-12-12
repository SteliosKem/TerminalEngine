#include "Math.h"

const float PI = 3.14159f;

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