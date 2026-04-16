#include <algorithm>
#include "Collision.h"

void handleXBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.right() > bounds.maxX) {
        gameObject.position.x = bounds.maxX - gameObject.size.x;
        gameObject.velocity.x = -gameObject.velocity.x;
    } else if (gameObject.left() < bounds.minX) {
        gameObject.position.x = bounds.minX;
        gameObject.velocity.x = -gameObject.velocity.x;
    }
}

void handleYBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.top() > bounds.maxY) {
        gameObject.position.y = bounds.maxY - gameObject.size.y;
        gameObject.velocity.y = -gameObject.velocity.y;
    } else if (gameObject.bottom() < bounds.minY) {
        gameObject.position.y = bounds.minY;
        gameObject.velocity.y = -gameObject.velocity.y;
    }
}

bool isOverlappingX(const GameObject& a, const GameObject& b) {
    return a.left() < b.right() && a.right() > b.left();
}

bool isOverlappingY(const GameObject& a, const GameObject& b) {
    return a.bottom() < b.top() && a.top() > b.bottom();
}

bool isColliding(const GameObject& a, const GameObject& b) {
    return isOverlappingX(a, b) && isOverlappingY(a, b);
}

float overlapX(const GameObject& a, const GameObject& b) {
    return std::min(a.right(), b.right()) - std::max(a.left(), b.left());
}

float overlapY(const GameObject& a, const GameObject& b) {
    return std::min(a.top(), b.top()) - std::max(a.bottom(), b.bottom());
}

void separateObjectsX(GameObject& a, GameObject& b) {
    float xOverlap = overlapX(a, b);
    float aCenterX = a.center().x;
    float bCenterX = b.center().x;
    if (aCenterX < bCenterX) {
        a.position.x = a.position.x - xOverlap / 2.0f;
        b.position.x = b.position.x + xOverlap / 2.0f;
    } else {
        a.position.x = a.position.x + xOverlap / 2.0f;
        b.position.x = b.position.x - xOverlap / 2.0f;
    }
}

void separateObjectsY(GameObject& a, GameObject& b) {
    float yOverlap = overlapY(a, b);
    float aCenterY = a.center().y;
    float bCenterY = b.center().y;
    if (aCenterY < bCenterY) {
        a.position.y = a.position.y - yOverlap / 2.0f;
        b.position.y = b.position.y + yOverlap / 2.0f;
    } else {
        a.position.y = a.position.y + yOverlap / 2.0f;
        b.position.y = b.position.y - yOverlap / 2.0f;
    }
}

void resolveCollisionX(GameObject& a, GameObject& b) {
    a.velocity.x = -a.velocity.x;
    b.velocity.x = -b.velocity.x;
    separateObjectsX(a, b);
}

void resolveCollisionY(GameObject& a, GameObject& b) {
    a.velocity.y = -a.velocity.y;
    b.velocity.y = -b.velocity.y;
    separateObjectsY(a, b);
}

// choose the axis with the least overlap
void resolveCollision(GameObject& a, GameObject& b) { // TEMPORARY
    float xOverlap = overlapX(a, b);
    float yOverlap = overlapY(a, b);
    if (xOverlap < yOverlap) {
        resolveCollisionX(a, b);
    } else {
        resolveCollisionY(a, b);
    }    
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}
