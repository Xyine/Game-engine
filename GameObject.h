#pragma once
#include <iostream>
#include "Vec2.h"

enum class ShapeType {
    Rectangle,
    Circle
};

struct GameObject {
    const char* name;
    ShapeType shapeType;
    Vec2 size;
    float radius;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    void move(float deltaTime) {
        Vec2 deltaPosition = velocity.scale(deltaTime);
        position = position.add(deltaPosition); 
    }

    Vec2 center() const {
        return Vec2{position.x + size.x / 2.0f, position.y + size.y / 2.0f};
    }

    float left() const { return position.x; }

    float right() const { return position.x + size.x; }
    
    float bottom() const { return position.y; }
    
    float top() const { return position.y + size.y; }

};

inline std::ostream& operator<<(std::ostream& os, const GameObject& gameObject) {
    os << gameObject.name << " size: " << gameObject.size
    << ", position: " << gameObject.position
    << ", center: " << gameObject.center()
    << ", bounds: "
    << "[left: " << gameObject.left() 
    << ", right: " << gameObject.right() 
    << ", bottom: " << gameObject.bottom() 
    << ", top: " << gameObject.top() 
    << "]"
    << ", velocity: " << gameObject.velocity
    << ", acceleration: " << gameObject.acceleration;

    return os;
}
