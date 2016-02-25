#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cmath>

#include "matrix3x3.h"

class Matrix3x3;

class Vector3f {
public:
    explicit Vector3f(const float &x = 0, const float &y = 0, const float &z = 0);
    Vector3f(const Vector3f &vec);
    ~Vector3f();

    Vector3f crossP(const Vector3f &vec) const;
    float length() const;
    float lengthSquared() const;
    void normalize();

    //Operators
    Vector3f operator+(const Vector3f &vec) const;
    Vector3f operator-(const Vector3f &vec) const;
    Vector3f &operator+=(const Vector3f &vec);
    Vector3f &operator*=(const float &scalar);
    Vector3f &operator/=(const float &scalar);
    Vector3f operator*(const float &val) const;
    Vector3f &operator=(const Vector3f &vec);
    bool operator==(const Vector3f &vec) const;
    bool operator!=(const Vector3f &vec) const;

    void rotate(const Vector3f &axis, const float &radians);
    inline float scalarP(const Vector3f &vec) const;

    float x = 0;
    float y = 0;
    float z = 0;
};

Vector3f crossP(const Vector3f &vec1, const Vector3f &vec2);
float scalarP(const Vector3f &vec1, const Vector3f &vec2);
Vector3f operator*(const float &val, const Vector3f &vec);
Vector3f operator/(const Vector3f &vec, const float &val);

namespace vec3f {
static const Vector3f origin(0.0f, 0.0f, 0.0f);
static const Vector3f xaxis(1.0f, 0.0f, 0.0f);
static const Vector3f yaxis(0.0f, 1.0f, 0.0f);
static const Vector3f zaxis(0.0f, 0.0f, 1.0f);
}

#endif // VECTOR3D_H
