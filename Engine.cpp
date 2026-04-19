#include <iostream>
#include "Engine.h"

Engine::Engine() : debugEnabled(true), isRunning(true), frame(0), maxFrames(3), deltaTime(0.5f), worldBounds{0.0f, 8.0f, 0.0f, 6.0f} {
    objects[0] = {"Player", ShapeType::Rectangle, {1.0f, 1.0f}, 0.0f, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}};
    objects[1] = {"Enemy", ShapeType::Rectangle, {1.0f, 1.0f}, 0.0f, {1.5f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}};
    objects[2] = {"Ball", ShapeType::Circle, {0.0f, 0.0f}, 0.15f, {4.0f, 3.0f}, {0.0f, 0.0f}, {0.0f, -3.8f}};
}

void Engine::updateState() {
    frame++;

    if (frame >= maxFrames) {
        isRunning = false;
    }
}

bool Engine::running() const {
    return isRunning;
}

void Engine::input() {
    if (debugEnabled) {
        std::cout << "Handling input...\n";
    }
}

void Engine::renderObjects() const {
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

void Engine::collisionSystemAllPairs() {
    for (int i = 0; i < objectCount; i++) {
        for (int j = i + 1; j < objectCount; j++) {
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
            }
        }
    }
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

void Engine::update() {
    input();
    if (debugEnabled) {
        std::cout << "World bounds: " << worldBounds << "\n";
        std::cout << "Updating frame...\n";
    }
    updateObjects();
    collisionSystemAllPairs();
    boundarySystem();
}

void Engine::render() const {
    if (debugEnabled) {
        std::cout << "Rendering frame...\n";
        renderObjects();
        std::cout << "---\n";
    }
}

void Engine::run() {
    while (running()) {
        if (debugEnabled) {
            std::cout << "Frame " << frame << "\n";
        }
        update();
        render();
        updateState();
    }
    if (debugEnabled) {
        std::cout << "Engine stopped.\n";
    }
}
