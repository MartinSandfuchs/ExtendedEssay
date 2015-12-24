#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <cmath>
#include <vector>

#include "vector3d.h"

class Vector3f;

const float Pi = 3.14156f;
using namespace std;
class Matrix3x3 {
public:
    Matrix3x3();

    Matrix3x3 makeObjectToWorld(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis);
    Matrix3x3 makeRotation(Vector3f axis, const float &angle);
    Matrix3x3 makeScale(const float &a, const float &b, const float &c);
    Matrix3x3 makeWorldToObject(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis);

    Matrix3x3 operator*(const float &s) const;

    vector< vector<float> > fields;
private:
};

Vector3f operator*(const Matrix3x3 &m, const Vector3f &vec);
Matrix3x3 operator*(const Matrix3x3 &m1, const Matrix3x3 &m2);

#endif // MATRIX3X3_H
