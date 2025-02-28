#ifndef _VECTOR2_H
#define _VECTOR2_H

#include <ostream>

class Vector2 {
    private:
    double x, y;

    public:
    Vector2(double _x, double _y) : x(_x), y(_y) {}

    double getX() const {
        return x;
    }
    
    double getY() const {
        return y;
    }

    void setX(double _x) {
        x = _x;
    }

    void setY(double _y) {
        y = _y;
    }

    Vector2 operator+(Vector2 const& vec) const;
    Vector2& operator+=(Vector2 const& vec);
    Vector2 operator-(Vector2 const& vec) const;
    Vector2& operator-=(Vector2 const& vec);
    Vector2 operator*(double scale) const;
    Vector2& operator*=(double scale);
    Vector2 operator/(double scale) const;
    Vector2& operator/=(double scale);

    double magnitude() const;
    
    Vector2 normal() const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector);
};

#endif