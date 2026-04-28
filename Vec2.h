#pragma once
#include <iostream>
#include <cmath>

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

    Vec2 subtract(const Vec2& other) const {
        return Vec2{x - other.x, y - other.y};
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalized() const {
        float len = length();
        if (len == 0.0f) {
            return Vec2{0.0f, 0.0f};
        }
        return Vec2{x / len, y / len};
    }

    float dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
