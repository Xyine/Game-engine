#include <iostream>
#include <array>
#include <algorithm>
#include "Vec2.h"
#include "Bounds.h"
#include "GameObject.h"

const int objectCount = 2;

void handleXBounds(GameObject& gameObject, const Bounds& bounds);
void handleYBounds(GameObject& gameObject, const Bounds& bounds);
bool isOverlappingX(const GameObject& a, const GameObject& b);
bool isOverlappingY(const GameObject& a, const GameObject& b);
bool isColliding(const GameObject& a, const GameObject& b);
float overlapX(const GameObject& a, const GameObject& b);
float overlapY(const GameObject& a, const GameObject& b);
void separateObjectsX(GameObject& a, GameObject& b);
void separateObjectsY(GameObject& a, GameObject& b);
void resolveCollisionX(GameObject& a, GameObject& b);
void resolveCollisionY(GameObject& a, GameObject& b);
void resolveCollision(GameObject& a, GameObject& b);
void renderSystem(const GameObject& gameObject);

struct Engine {
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration
    float deltaTime;
    Bounds worldBounds;
    std::array<GameObject, objectCount> objects;
    
    Engine() : isRunning(true), frame(0), maxFrames(3), deltaTime(0.5f), worldBounds{0.0f, 3.0f, 0.0f, 6.0f} {
        objects[0] = {"Player", {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}};
        objects[1] = {"Enemy", {1.0f, 1.0f}, {1.5f, 0.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}};
    }

    void updateState() {
        frame++;

        if (frame >= maxFrames) {
            isRunning = false;
        }
    }

    bool running() const {
        return isRunning;
    }

    void input() {
        std::cout << "Handling input...\n";
    }

    void renderObjects() const {
        for (const GameObject& object : objects) {
            renderSystem(object);
        }
    }

    bool areObjectsColliding(int i, int j) const {
        return isColliding(objects[i], objects[j]);
    }

    void resolveObjectsCollision(int i, int j) {
        resolveCollision(objects[i], objects[j]);
    }

    void collisionSystemAllPairs() {
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

    void physicsSystem() {
        for (GameObject& object : objects) {
            Vec2 deltaVelocity = object.acceleration.scale(deltaTime);
            object.velocity = object.velocity.add(deltaVelocity);
        }
    }

    void movementSystem() {
        for (GameObject& object : objects) {
            object.move(deltaTime);
        }
    }
    
    void boundarySystem() {
        for (GameObject& object : objects) {
            handleXBounds(object, worldBounds);
            handleYBounds(object, worldBounds);
        }
    }

    void updateObjects() {
        physicsSystem();
        movementSystem();
    }

    void update() {
        input();
        std::cout << "World bounds: ";
        worldBounds.print();
        std::cout << "\n";
        std::cout << "Updating frame...\n";
        updateObjects();
        collisionSystemAllPairs();
        boundarySystem();
    }

    void render() const {
        std::cout << "Rendering frame...\n";
        renderObjects();
        std::cout << "---\n";
    }

    void run() {
        while (running()) {
            std::cout << "Frame " << frame << "\n";
            update();
            render();
            updateState();
        }
        
        std::cout << "Engine stopped.\n";
    }
};

int main() {
    Engine engine;
    engine.run();
    
    return 0;
}

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
