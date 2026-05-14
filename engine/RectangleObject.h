#pragma once
#include "GameObject.h"

class RectangleObject : public GameObject {
public:
    Vec2 size;

    RectangleObject(
        std::string name,
        BodyType bodyType,
        Vec2 size,
        Vec2 position,
        Vec2 velocity,
        Vec2 acceleration
    )
        : GameObject(name, bodyType, position, velocity, acceleration),
          size(size)
    {}

    ShapeType shapeType() const override {
        return ShapeType::Rectangle;
    }
    
    Vec2 getSize() const override {
        return size;
    }

    Vec2 center() const override {
        return Vec2{
            position.x + size.x / 2.0f,
            position.y + size.y / 2.0f
        };
    }

    float left() const override {
        return position.x;
    }

    float right() const override {
        return position.x + size.x;
    }

    float bottom() const override {
        return position.y;
    }

    float top() const override {
        return position.y + size.y;
    }

    void print(std::ostream& os) const override {
        os << name << " size: " << size;
        os << ", position: " << position
           << ", center: " << center()
           << ", bounds: "
           << "[left: " << left()
           << ", right: " << right()
           << ", bottom: " << bottom()
           << ", top: " << top()
           << "]"
           << ", velocity: " << velocity
           << ", acceleration: " << acceleration;
    }
};
