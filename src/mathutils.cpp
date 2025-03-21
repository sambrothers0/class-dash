#include "mathutils.hpp"

namespace mathutils {
    bool isBetween(double num, double low, double high) {
        return num >= low && num <= high;
    }

    double clamp(double num, double low, double high) {
        if (num < low) {
            return low;
        } else if (num > high) {
            return high;
        } else {
            return num;
        }
    }
}