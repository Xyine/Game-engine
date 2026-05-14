#pragma once
#include "GameObject.h"

class CircleObject : public GameObject {
public:
    float radius;

    CircleObject(
        std::string name,
        BodyType bodyType,
        float radius,
        Vec2 position,
        Vec2 velocity,
        Vec2 acceleration
    )
        : GameObject(name, bodyType, position, velocity, acceleration),
          radius(radius)
    {}

    Vec2 center() const override {
        return position;
    }

    float left() const override {
        return position.x - radius;
    }

    float right() const override {
        return position.x + radius;
    }

    float bottom() const override {
        return position.y - radius;
    }

    float top() const override {
        return position.y + radius;
    }

    ShapeType shapeType() const override {
        return ShapeType::Circle;
    }

    float getRadius() const override {
        return radius;
    }

    void print(std::ostream& os) const override {
        os << name << " radius: " << radius;
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
