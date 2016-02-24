#include "matrix3x3.h"

Matrix3x3::Matrix3x3() {
	fields.resize(3);
	for (unsigned int i = 0; i < fields.size(); ++i) {
		fields.at(i).resize(3, 0.0f);
	}
}

Matrix3x3 Matrix3x3::makeObjectToWorld(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis) {
	Matrix3x3 result;
	result.fields.at(0).at(0) = xaxis.x; result.fields.at(0).at(1) = yaxis.x; result.fields.at(0).at(2) = zaxis.x;
	result.fields.at(1).at(0) = xaxis.y; result.fields.at(1).at(1) = yaxis.y; result.fields.at(1).at(2) = zaxis.y;
	result.fields.at(2).at(0) = xaxis.z; result.fields.at(2).at(1) = yaxis.z; result.fields.at(2).at(2) = zaxis.z;
	return result;
}

Matrix3x3 Matrix3x3::makeRotation(Vector3f axis, const float &angle) {
	if (axis.lengthSquared() != 1.0f)
		axis.normalize();

	const float cosPhi = cosf(angle);
	const float sinPhi = sinf(angle);
	const float oneMinCos = 1 - cosPhi;
	Matrix3x3 result;

	result.fields.at(0).at(0) = cosPhi + axis.x * axis.x * oneMinCos;
	result.fields.at(0).at(1) = axis.x * axis.y * oneMinCos - axis.z * sinPhi;
	result.fields.at(0).at(2) = axis.x * axis.z * oneMinCos + axis.y * sinPhi;

	result.fields.at(1).at(0) = axis.y * axis.x * oneMinCos + axis.z * sinPhi;
	result.fields.at(1).at(1) = cosPhi + axis.y * axis.y * oneMinCos;
	result.fields.at(1).at(2) = axis.y * axis.z * oneMinCos - axis.x * sinPhi;

	result.fields.at(2).at(0) = axis.z * axis.x * oneMinCos - axis.y * sinPhi;
	result.fields.at(2).at(1) = axis.z * axis.y * oneMinCos + axis.x * sinPhi;
	result.fields.at(2).at(2) = cosPhi + axis.z * axis.z * oneMinCos;
	return result;
}

Matrix3x3 Matrix3x3::makeScale(const float &a, const float &b, const float &c) {
	Matrix3x3 result;
	/*fields.resize(3);
	   for (unsigned int i = 0; i < 3; ++i) {
	        fields.at(i).resize(3,0);
	   }*/
	result.fields.at(0).at(0) = a;
	result.fields.at(1).at(1) = b;
	result.fields.at(2).at(2) = c;
	return result;
}
Matrix3x3 Matrix3x3::makeWorldToObject(const Vector3f &xaxis, const Vector3f &yaxis, const Vector3f &zaxis) {
	Matrix3x3 result;
	result.fields.at(0).at(0) = xaxis.x; result.fields.at(0).at(1) = xaxis.y; result.fields.at(0).at(2) = xaxis.z;
	result.fields.at(1).at(0) = yaxis.x; result.fields.at(1).at(1) = yaxis.y; result.fields.at(1).at(2) = yaxis.z;
	result.fields.at(2).at(0) = zaxis.x; result.fields.at(2).at(1) = zaxis.y; result.fields.at(2).at(2) = zaxis.z;
	return result;
}

Matrix3x3 Matrix3x3::operator*(const float &s) const {
	Matrix3x3 m = *this;
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 3; ++j) {
			m.fields.at(i).at(j) = m.fields.at(i).at(j) * s;
		}
	}
	return m;
}

//Non member functions
Vector3f operator*(const Matrix3x3 &m, const Vector3f &vec) {
	Vector3f result;
	result.x = m.fields.at(0).at(0) * vec.x + m.fields.at(0).at(1) * vec.y + m.fields.at(0).at(2) * vec.z;
	result.y = m.fields.at(1).at(0) * vec.x + m.fields.at(1).at(1) * vec.y + m.fields.at(1).at(2) * vec.z;
	result.z = m.fields.at(2).at(0) * vec.x + m.fields.at(2).at(1) * vec.y + m.fields.at(2).at(2) * vec.z;
	return result;
}
Matrix3x3 operator*(const Matrix3x3 &m1, const Matrix3x3 &m2) {
	Matrix3x3 result;
	//Iterate through the rows of the first matrix
	for (unsigned int i = 0; i < m1.fields.size(); ++i) {
		//Iterate through the columns of the second matrix
		for (unsigned int j = 0; j < m2.fields.at(0).size(); ++j) {
			float currentField = 0;
			//Iterate through rows of column j in matrix m2
			for (unsigned int k = 0; k < m2.fields.at(j).size(); ++k) {
				currentField += m2.fields.at(k).at(j) * m1.fields.at(i).at(k);
			}
			result.fields.at(i).at(j) = currentField;
		}
	}
	return result;
}
