#include "Render.h"

sf::Vector2f worldToScreenPosition(const GameObject& object, float scale, float windowHeight) {
    return {object.position.x * scale, windowHeight - (object.position.y + object.size.y) * scale};
}

sf::Vector2f worldToScreenSize(const GameObject& object, float scale) {
    return {
        object.size.x * scale,
        object.size.y * scale
    };
}
