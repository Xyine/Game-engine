#pragma once
#include "CircleObject.h"

class RingObject : public CircleObject {
public:
    RingObject(
        std::string name,
        BodyType bodyType,
        float radius,
        Vec2 position,
        Vec2 velocity,
        Vec2 acceleration
    )
        : CircleObject(name, bodyType, radius, position, velocity, acceleration)
    {}

    ShapeType shapeType() const override {
        return ShapeType::Ring;
    }
};