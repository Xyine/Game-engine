#pragma once
#include <iostream>
#include "Vec2.h"

enum class ShapeType {
    Rectangle,
    Circle
};

enum class BodyType {
    Static,
    Kinematic,
    Dynamic,
    Character
};

struct GameObject {
    const char* name;
    ShapeType shapeType;
    BodyType bodyType;
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
        if (shapeType == ShapeType::Rectangle) {
            return Vec2{position.x + size.x / 2.0f, position.y + size.y / 2.0f};
        } else {
            return position;
        }
    }

    float left() const {
        if (shapeType == ShapeType::Rectangle) {
            return position.x;
        } else {
            return position.x - radius;
        }
    }

    float right() const {
        if (shapeType == ShapeType::Rectangle) {
            return position.x + size.x;
        } else {
            return position.x + radius;
        }
    }
    
    float bottom() const { 
        if (shapeType == ShapeType::Rectangle) {
            return position.y;
        } else {
            return position.y - radius;
        }
    }
    
    float top() const {
        if (shapeType == ShapeType::Rectangle) {
            return position.y + size.y;
        } else {
            return position.y + radius;
        }
    }

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
