#pragma once
#include <iostream>
#include <string>
#include "Vec2.h"

enum class BodyType {
    Static,
    Kinematic,
    Dynamic,
    Character
};

enum class ShapeType {
    Rectangle,
    Circle,
    Ring
};


class GameObject {
public:
    std::string name;
    BodyType bodyType;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    bool isBroken;

    GameObject(
        std::string name,
        BodyType bodyType,
        Vec2 position,
        Vec2 velocity,
        Vec2 acceleration
    )
        : name(name),
          bodyType(bodyType),
          position(position),
          velocity(velocity),
          acceleration(acceleration),
          isBroken(false)
    {}

    virtual ~GameObject() = default;

    virtual ShapeType shapeType() const = 0;

    virtual Vec2 getSize() const {
        return Vec2{0.0f, 0.0f};
    }
    
    virtual float getRadius() const {
        return 0.0f;
    }

    void move(float deltaTime) {
        Vec2 deltaPosition = velocity.scale(deltaTime);
        position = position.add(deltaPosition);
    }

    virtual Vec2 center() const = 0;
    virtual float left() const = 0;
    virtual float right() const = 0;
    virtual float bottom() const = 0;
    virtual float top() const = 0;

    virtual void print(std::ostream& os) const {
        os << name
           << ", position: " << position
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

inline std::ostream& operator<<(std::ostream& os, const GameObject& object) {
    object.print(os);
    return os;
}
