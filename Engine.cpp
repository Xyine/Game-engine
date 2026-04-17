#include <iostream>
#include "Engine.h"

Engine::Engine() : isRunning(true), frame(0), maxFrames(3), deltaTime(0.5f), worldBounds{0.0f, 3.0f, 0.0f, 6.0f} {
    objects[0] = {"Player", {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}};
    objects[1] = {"Enemy", {1.0f, 1.0f}, {1.5f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}};
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
    std::cout << "Handling input...\n";
}

void Engine::renderObjects() const {
    for (const GameObject& object : objects) {
        renderSystem(object);
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
            std::cout 
            << "Checking collision between "
            << objects[i].name
            << " and "
            << objects[j].name
            << "...\n";

            if (areObjectsColliding(i, j)) {
                std::cout 
                << "Collision detected between "
                << objects[i].name
                << " and "
                << objects[j].name
                << "\n";
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
    std::cout << "World bounds: " << worldBounds << "\n";
    std::cout << "Updating frame...\n";
    updateObjects();
    collisionSystemAllPairs();
    boundarySystem();
}

void Engine::render() const {
    std::cout << "Rendering frame...\n";
    renderObjects();
    std::cout << "---\n";
}

void Engine::run() {
    while (running()) {
        std::cout << "Frame " << frame << "\n";
        update();
        render();
        updateState();
    }
    
    std::cout << "Engine stopped.\n";
}
