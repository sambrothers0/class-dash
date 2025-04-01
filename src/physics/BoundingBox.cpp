#include "physics/BoundingBox.hpp"

#include <cmath>

double BoundingBox::getTopY() const {
    return offset.getY();
}

double BoundingBox::getBottomY() const {
    return offset.getY() + size.getY();
}

double BoundingBox::getLeftX() const {
    return offset.getX();
}

double BoundingBox::getRightX() const {
    return offset.getX() + size.getX();
}