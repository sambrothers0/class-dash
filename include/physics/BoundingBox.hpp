#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "physics/Vector2.hpp"

// Rectangular bounding box (based on offset from position)
class BoundingBox {
    private:
    Vector2 offset; // Offset
    Vector2 size;

    public:
    BoundingBox(Vector2 _offset, Vector2 _size) : offset(_offset), size(_size) {}

    const Vector2& getOffset() const {
        return offset;
    }

    const Vector2& getSize() const {
        return size;
    }

    double getTopY() const;
    double getBottomY() const;
    double getLeftX() const;
    double getRightX() const;

    // Returns if 2 bounding boxes overlap
    bool overlaps(const BoundingBox& box) const;

    BoundingBox operator+(Vector2 const& vec) const {
        return BoundingBox(offset + vec, size);
    }
};

#endif