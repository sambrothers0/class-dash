#ifndef _MATH_UTILS_H
#define _MATH_UTILS_H

namespace mathutils {
    bool isBetween(double num, double low, double high);

    double clamp(double num, double low, double high);

    // Rounds a number down to the nearest interval
    double floorInterval(double num, double interval);
}

#endif