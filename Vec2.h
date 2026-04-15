#pragma once
#include <iostream>

struct Vec2 {
    float x;
    float y;

    void add(const Vec2& other, float deltaTime) {
        x += other.x * deltaTime;
        y += other.y * deltaTime;
    }

    Vec2 add(const Vec2& other) const {
        return Vec2{x + other.x, y + other.y};
    }

    Vec2 scale(float scalar) const {
        return Vec2{x * scalar, y * scalar};
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};
