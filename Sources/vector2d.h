#pragma once


class Vector2i{
public:
    Vector2i(const int &x = 0, const int &y = 0) :
        x(x), y(y) {
    }
    int x;
    int y;
};

class Vector2f {
 public:
    Vector2f(const float &x = 0, const float &y = 0);
    Vector2f& operator=(const Vector2f &other);

    Vector2f operator+(const Vector2f &vec) const;
    Vector2f operator-(const Vector2f &vec) const;
    Vector2f operator*(const float &val) const;
    bool operator!=(const Vector2f &vec) const;
    bool operator==(const Vector2f &vec) const;

    float x;
    float y;
};
