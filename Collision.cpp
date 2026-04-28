#include <algorithm>
#include "Collision.h"

bool isAffectedByCollision(const GameObject& gameObject) {
    return gameObject.bodyType == BodyType::Character
        || gameObject.bodyType == BodyType::Dynamic;
}

void handleXBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.right() > bounds.maxX) {
        gameObject.position.x = (gameObject.shapeType == ShapeType::Rectangle)
            ? bounds.maxX - gameObject.size.x
            : bounds.maxX - gameObject.radius;
        gameObject.velocity.x = -gameObject.velocity.x;
    } else if (gameObject.left() < bounds.minX) {
        gameObject.position.x = (gameObject.shapeType == ShapeType::Rectangle)
            ? bounds.minX
            : bounds.minX + gameObject.radius;
        gameObject.velocity.x = -gameObject.velocity.x;
    }
}

void handleYBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.top() > bounds.maxY) {
        gameObject.position.y = (gameObject.shapeType == ShapeType::Rectangle)
            ? bounds.maxY - gameObject.size.y
            : bounds.maxY - gameObject.radius;
        gameObject.velocity.y = -gameObject.velocity.y;
    } else if (gameObject.bottom() < bounds.minY) {
        gameObject.position.y = (gameObject.shapeType == ShapeType::Rectangle)
            ? bounds.minY
            : bounds.minY + gameObject.radius;
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
    if (a.isBroken || b.isBroken) {
        return false;
    }

    if (a.shapeType == ShapeType::Circle && b.shapeType == ShapeType::Ring) {
        return isCircleCollidingWithRing(a, b);
    }

    if (a.shapeType == ShapeType::Ring && b.shapeType == ShapeType::Circle) {
        return isCircleCollidingWithRing(b, a);
    }

    if (a.shapeType == ShapeType::Ring || b.shapeType == ShapeType::Ring) {
        return false;
    }

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
    if (isAffectedByCollision(a) && isAffectedByCollision(b)) {
        if (aCenterX < bCenterX) {
            a.position.x = a.position.x - xOverlap / 2.0f;
            b.position.x = b.position.x + xOverlap / 2.0f;
        } else {
            a.position.x = a.position.x + xOverlap / 2.0f;
            b.position.x = b.position.x - xOverlap / 2.0f;
        }
    } else if (isAffectedByCollision(a)) {
        if (aCenterX < bCenterX) {
            a.position.x = a.position.x - xOverlap;
        } else {
            a.position.x = a.position.x + xOverlap;
        }
    } else if (isAffectedByCollision(b)) {
        if (aCenterX < bCenterX) {
            b.position.x = b.position.x + xOverlap;
        } else {
            b.position.x = b.position.x - xOverlap;
        }
    }
}

void separateObjectsY(GameObject& a, GameObject& b) {
    float yOverlap = overlapY(a, b);
    float aCenterY = a.center().y;
    float bCenterY = b.center().y;
    if (isAffectedByCollision(a) && isAffectedByCollision(b)) {
        if (aCenterY < bCenterY) {
            a.position.y = a.position.y - yOverlap / 2.0f;
            b.position.y = b.position.y + yOverlap / 2.0f;
        } else {
            a.position.y = a.position.y + yOverlap / 2.0f;
            b.position.y = b.position.y - yOverlap / 2.0f;
        }
    } else if (isAffectedByCollision(a)) {
        if (aCenterY < bCenterY) {
            a.position.y = a.position.y - yOverlap ;
        } else {
            a.position.y = a.position.y + yOverlap;
        }
    } else if (isAffectedByCollision(b)) {
        if (aCenterY < bCenterY) {
            b.position.y = b.position.y + yOverlap;
        } else {
            b.position.y = b.position.y - yOverlap;
        }
    }
}

void resolveCollisionX(GameObject& a, GameObject& b) {
     if (isAffectedByCollision(a)) {
        a.velocity.x = -a.velocity.x;
    }
    if (isAffectedByCollision(b)) {
        b.velocity.x = -b.velocity.x;
    }
    separateObjectsX(a, b);
}

void resolveCollisionY(GameObject& a, GameObject& b) {
     if (isAffectedByCollision(a)) {
        a.velocity.y = -a.velocity.y;
    }
    if (isAffectedByCollision(b)) {
        b.velocity.y = -b.velocity.y;
    }
    separateObjectsY(a, b);
}

// choose the axis with the least overlap
void resolveCollision(GameObject& a, GameObject& b) { // TEMPORARY
    if (a.isBroken || b.isBroken) {
        return;
    }

    if (a.shapeType == ShapeType::Circle && b.shapeType == ShapeType::Ring) {
        resolveCircleRingCollision(a, b);
        return;
    }

    if (a.shapeType == ShapeType::Ring && b.shapeType == ShapeType::Circle) {
        resolveCircleRingCollision(b, a);
        return;
    }

    float xOverlap = overlapX(a, b);
    float yOverlap = overlapY(a, b);

    if (xOverlap < yOverlap) {
        resolveCollisionX(a, b);
    } else {
        resolveCollisionY(a, b);
    }
}

bool isCircleCollidingWithRing(const GameObject& circle, const GameObject& ring) {
    Vec2 toCircle = circle.center().subtract(ring.center());
    float distance = toCircle.length();

    float innerTouchDistance = ring.radius - circle.radius;

    if (distance < innerTouchDistance) {
        return false;
    }

    Vec2 normal = toCircle.normalized();
    float velocityAlongNormal = circle.velocity.dot(normal);

    return velocityAlongNormal > 0.0f;
}

void resolveCircleRingCollision(GameObject& circle, GameObject& ring) {
    Vec2 toCircle = circle.center().subtract(ring.center());
    Vec2 normal = toCircle.normalized();

    float innerLimit = ring.radius - circle.radius;

    circle.position = ring.center().add(normal.scale(innerLimit));

    float velocityAlongNormal = circle.velocity.dot(normal);

    circle.velocity = circle.velocity.subtract(
        normal.scale(2.0f * velocityAlongNormal)
    );

    ring.isBroken = true;
}
