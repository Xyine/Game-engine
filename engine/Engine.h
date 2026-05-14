#pragma once
#include <vector>
#include "Collision.h"
#include <memory>



struct CollisionEvent {
    size_t firstObjectIndex;
    size_t secondObjectIndex;
};

struct CollisionReport {
    std::vector<CollisionEvent> events;

    int count() const {
        return static_cast<int>(events.size());
    }
};

struct UpdateReport {
    CollisionReport collisions;
};

struct Engine {
    bool debugEnabled;
    float deltaTime;
    Bounds worldBounds;
    std::vector<std::unique_ptr<GameObject>> objects;

    Engine();
    void debugPrintObjects() const;
    bool areObjectsColliding(int i, int j) const;
    void resolveObjectsCollision(int i, int j);
    CollisionReport collisionSystemAllPairs();
    void physicsSystem();
    void movementSystem();
    void boundarySystem();
    void updateObjects();
    UpdateReport update();
    void reset();
};
