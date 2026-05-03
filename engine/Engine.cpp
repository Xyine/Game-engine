#include <iostream>
#include "Engine.h"

Engine::Engine() : debugEnabled(true), isRunning(true), frame(0), maxFrames(1000), deltaTime(0.016f), worldBounds{0.0f, 8.0f, 0.0f, 6.0f}, score{0} {

    // BALL (index 0)
    objects.push_back({
        "Ball",
        ShapeType::Circle,
        BodyType::Dynamic,
        {0.0f, 0.0f},
        0.15f,
        {4.0f, 3.0f},
        {3.5f, 0.0f},
        {0.0f, -3.8f},
        false
    });

    // RINGS (index 1 → 100)
    float maxRadius = 2.8f;
    float startRadius = 0.3f;
    float spacing = (maxRadius - startRadius) / 99.0f;

    for (int i = 0; i < 100; i++) {
        objects.push_back({
            "Ring",
            ShapeType::Ring,
            BodyType::Static,
            {0.0f, 0.0f},
            startRadius + i * spacing,
            {4.0f, 3.0f},
            {0.0f, 0.0f},
            {0.0f, 0.0f},
            false
        });
    }
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
                score ++;
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

void Engine::reset() {
    *this = Engine();
}
