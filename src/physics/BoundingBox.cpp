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

bool BoundingBox::overlaps(const BoundingBox& box) const {
    if (getRightX() < box.getLeftX()) {
        return false;
    } else if (getLeftX() > box.getRightX()) {
        return false;
    } else if (getTopY() > box.getBottomY()) {
        return false;
    } else if (getBottomY() < box.getTopY()) {
        return false;
    }

    return true;
}