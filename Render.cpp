#include "Render.h"

sf::Vector2f worldToScreenPosition(const GameObject& object, float scale, float windowHeight) {
    if (object.shapeType == ShapeType::Rectangle) {
        return {object.position.x * scale, windowHeight - (object.position.y + object.size.y) * scale};
    } else {
        return {object.position.x * scale - object.radius * scale, windowHeight - object.position.y * scale - object.radius * scale};
    }
}

sf::Vector2f worldToScreenSize(const GameObject& object, float scale) {
    return {
        object.size.x * scale,
        object.size.y * scale
    };
}

float worldToScreenRadius(const GameObject& object, float scale) {
    return object.radius * scale;
}
