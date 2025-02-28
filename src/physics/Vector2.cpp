#include "physics/Vector2.hpp"

#include <cmath>

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2& Vector2::operator+=(const Vector2& other) {
    *this = *this + other;
    return *this;
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator-=(const Vector2& other) {
    *this = *this - other;
    return *this;
}

Vector2 Vector2::operator*(double scale) const {
    return Vector2(x * scale, y * scale);
}

Vector2& Vector2::operator*=(double scale) {
    *this = *this * scale;
    return *this;
}

Vector2 Vector2::operator/(double scale) const {
    return Vector2(x / scale, y / scale);
}

Vector2& Vector2::operator/=(double scale) {
    *this = *this / scale;
    return *this;
}

double Vector2::magnitude() const {
    return sqrt(x * x + y * y);
}

Vector2 Vector2::normal() const {
    double mag = magnitude();

    return mag == 0 ? *this : *this / mag;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vector) {
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}