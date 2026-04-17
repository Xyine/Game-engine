#pragma once
#include <iostream>

struct Bounds {
    float minX;
    float maxX;
    float minY;
    float maxY;
};

inline std::ostream& operator<<(std::ostream& os, const Bounds& bounds) {
    os << "[minX: " << bounds.minX 
                  << ", maxX: " << bounds.maxX 
                  << ", minY: " << bounds.minY 
                  << ", maxY: " << bounds.maxY 
                  << "]";
    return os;
}
