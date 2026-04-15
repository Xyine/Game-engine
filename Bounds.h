#pragma once
#include <iostream>

struct Bounds {
    float minX;
    float maxX;
    float minY;
    float maxY;

    void print() const {
        std::cout << "[minX: " << minX 
                  << ", maxX: " << maxX 
                  << ", minY: " << minY 
                  << ", maxY: " << maxY 
                  << "]";
    }
};
