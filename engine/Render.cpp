#include "Render.h"

sf::Vector2f worldToScreenPosition(const GameObject& object, float scale, float windowHeight) {
    if (object.shapeType() == ShapeType::Rectangle) {
        return {object.position.x * scale, windowHeight - (object.position.y + object.getSize().y) * scale};
    } else {
        return {object.position.x * scale - object.getRadius() * scale, windowHeight - object.position.y * scale - object.getRadius() * scale};
    }
}

sf::Vector2f worldToScreenSize(const GameObject& object, float scale) {
    return {
        object.getSize().x * scale,
        object.getSize().y * scale
    };
}

float worldToScreenRadius(const GameObject& object, float scale) {
    return object.getRadius() * scale;
}
