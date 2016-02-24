#include "vector2d.h"

Vector2f::Vector2f(const float &x, const float &y) :
	x(x), y(y) {
}

Vector2f& Vector2f::operator=(const Vector2f &other) {
	this->x = other.x;
	this->y = other.y;
	return *this;
}

//Operators
Vector2f Vector2f::operator+(const Vector2f &vec) const {
	return Vector2f(this->x + vec.x, this->y + vec.y);
}

Vector2f Vector2f::operator-(const Vector2f &vec) const {
	return Vector2f(x - vec.x, y - vec.y);
}

Vector2f Vector2f::operator*(const float &val) const {
	return Vector2f(x * val, y * val);
}

bool Vector2f::operator!=(const Vector2f &vec) const {
	return x != vec.x || y != vec.y;
}
bool Vector2f::operator==(const Vector2f &vec) const {
	return x == vec.x && y == vec.y;
}
