#include <iostream>
#include "Engine.h"

Engine::Engine() : debugEnabled(false), deltaTime(0.0f), worldBounds{0.0f, 0.0f, 0.0f, 0.0f} {}

void Engine::debugPrintObjects() const {
    for (const GameObject& object : objects) {
        std::cout << object << "\n";
    }
}

bool Engine::areObjectsColliding(int i, int j) const {
    return isColliding(objects[i], objects[j]);
}

void Engine::resolveObjectsCollision(int i, int j) {
    resolveCollision(objects[i], objects[j]);
}

CollisionReport Engine::collisionSystemAllPairs() {
    CollisionReport report;

    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = i + 1; j < objects.size(); j++) {

            if (debugEnabled) {
                std::cout 
                << "Checking collision between "
                << objects[i].name
                << " and "
                << objects[j].name
                << "...\n";
            }

            if (areObjectsColliding(i, j)) {
                if (debugEnabled) {
                    std::cout 
                    << "Collision detected between "
                    << objects[i].name
                    << " and "
                    << objects[j].name
                    << "\n";
                }
                resolveObjectsCollision(i, j);
                report.events.push_back({i, j});
            }
        }
    }
    return report;
}

void Engine::physicsSystem() {
    for (GameObject& object : objects) {
        Vec2 deltaVelocity = object.acceleration.scale(deltaTime);
        object.velocity = object.velocity.add(deltaVelocity);
    }
}

void Engine::movementSystem() {
    for (GameObject& object : objects) {
        object.move(deltaTime);
    }
}

void Engine::boundarySystem() {
    for (GameObject& object : objects) {
        handleXBounds(object, worldBounds);
        handleYBounds(object, worldBounds);
    }
}

void Engine::updateObjects() {
    physicsSystem();
    movementSystem();
}

UpdateReport Engine::update() {
    if (debugEnabled) {
        std::cout << "World bounds: " << worldBounds << "\n";
        std::cout << "Updating frame...\n";
    }

    UpdateReport report;

    updateObjects();
    report.collisions = collisionSystemAllPairs();
    boundarySystem();

    return report;
}


void Engine::reset() {
    *this = Engine();
}
