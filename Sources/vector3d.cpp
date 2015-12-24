#include "vector3d.h"

Vector3f::Vector3f(const float &x, const float &y, const float &z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
Vector3f::Vector3f(const Vector3f &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

Vector3f::~Vector3f() {

}

Vector3f Vector3f::crossP(const Vector3f &vec) const {
    return Vector3f(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
}

float Vector3f::length() const {
    return sqrtf(x*x + y*y + z*z);
}

float Vector3f::lengthSquared() const {
    return x*x + y*y + z*z;
}

void Vector3f::normalize() {
    const float length = this->length();
    x /= length;
    y /= length;
    z /= length;
}

//Operators
Vector3f Vector3f::operator+(const Vector3f &vec) const {
    return Vector3f(x+vec.x, y+vec.y, z+vec.z);
}

Vector3f Vector3f::operator-(const Vector3f &vec) const {
    return Vector3f(x-vec.x, y-vec.y, z-vec.z);
}

Vector3f &Vector3f::operator+=(const Vector3f &vec) {
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3f &Vector3f::operator*=(const float &scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Vector3f &Vector3f::operator/=(const float &scalar) {
    *this = *this*(1.0f/scalar);
    return *this;
}

Vector3f Vector3f::operator*(const float &val) const {
    return Vector3f(x*val, y*val, z*val);
}

Vector3f &Vector3f::operator=(const Vector3f &vec) {
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

bool Vector3f::operator==(const Vector3f &vec) const {
    return vec.x==x && vec.y==y && vec.z==z;
}

bool Vector3f::operator!=(const Vector3f &vec) const {
    return vec.x!=x || vec.y!=y || vec.z!=z;
}

//Other functions
void Vector3f::rotate(const Vector3f &axis, const float &radians) {
    /*Quaternion v(0,x,y,z);
    Quaternion q(0,axis.x, axis.y, axis.z);
    q = q.makeRotation(radians);
    v = q*v*q.conjugate();

    x = v.q1;
    y = v.q2;
    z = v.q3;*/
    const Matrix3x3 rotMat = Matrix3x3().makeRotation(axis, radians);
    *this = rotMat**this;
}
float Vector3f::scalarP(const Vector3f &vec) const {
    return x*vec.x + y*vec.y + z*vec.z;
}

//Non member functions
Vector3f crossP(const Vector3f &vec1, const Vector3f &vec2) {
    return Vector3f(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}
float scalarP(const Vector3f &vec1, const Vector3f &vec2) {
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}
Vector3f operator*(const float &val, const Vector3f &vec) {
    return Vector3f(val*vec.x, val*vec.y, val*vec.z);
}


Vector3f operator/(const Vector3f &vec, const float &val) {
    return Vector3f(vec.x/val, vec.y/val, vec.z/val);
}
