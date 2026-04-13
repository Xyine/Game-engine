#include <iostream>
#include <array>

const int objectCount = 2;

struct Bounds {
    float minX;
    float maxX;
    float minY;
    float maxY;

    void print() const {
        std::cout << "[minX: " << minX 
                  << ", maxX: " << maxX 
                  << ", minY: " << minY 
                  << ", maxY: " << maxY 
                  << "]";
    }
};

struct Vec2 {
    float x;
    float y;

    void add(const Vec2& other, float deltaTime) {
        x += other.x * deltaTime;
        y += other.y * deltaTime;
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};

struct GameObject {
    const char* name;
    Vec2 size;
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    void print() const {
        std::cout << name << " size: ";
        size.print();
        std::cout << ", position: ";
        position.print();
        std::cout << ", center: ";
        center().print();
        std::cout << ", velocity: ";
        velocity.print();
        std::cout << ", acceleration: ";
        acceleration.print();
        std::cout << "\n";
    }

    void move(float deltaTime) { position.add(velocity, deltaTime); }

    Vec2 center() const {
        return Vec2{position.x + size.x / 2.0f, position.y + size.y / 2.0f};
    }
};

void movementSystem(GameObject& gameObject, float deltaTime);
void physicsSystem(GameObject& gameObject, float deltaTime);
void handleXBounds(GameObject& gameObject, const Bounds& bounds);
void handleYBounds(GameObject& gameObject, const Bounds& bounds);
void boundarySystem(GameObject& gameObject, const Bounds& bounds);
bool isOverlappingX(const GameObject& a, const GameObject& b);
bool isOverlappingY(const GameObject& a, const GameObject& b);
bool isColliding(const GameObject& a, const GameObject& b);
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
        objects[0] = {"Player", {1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}};
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

    void updateObjects() {
        for (GameObject& object : objects) {
            physicsSystem(object, deltaTime);
            movementSystem(object, deltaTime);
            boundarySystem(object, worldBounds);
        }
    }

    void renderObjects() const {
        for (const GameObject& object : objects) {
            renderSystem(object);
        }
    }

    bool firstTwoObjectsAreColliding() const {
        return isColliding(objects[0], objects[1]);
    }

    void processFrame() {
        std::cout << "Frame " << frame << "\n";
        input();
        std::cout << "World bounds: ";
        worldBounds.print();
        std::cout << "\n";
        std::cout << "Updating frame...\n";
        updateObjects();
        std::cout << "Checking collision between " 
                  << objects[0].name 
                  << " and " 
                  << objects[1].name 
                  << "...\n";
        if (firstTwoObjectsAreColliding()) {
            std::cout << "Collision detected between "
                      << objects[0].name
                      << " and "
                      << objects[1].name
                      << "\n";
            resolveCollision(objects[0], objects[1]);
        }
        std::cout << "Rendering frame...\n";
        renderObjects();
        std::cout << "---\n";
    }

    void run() {
        while (running()) {
            processFrame();
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

void movementSystem(GameObject& gameObject, float deltaTime) {
    gameObject.move(deltaTime);
}

void physicsSystem(GameObject& gameObject, float deltaTime) {
    gameObject.velocity.add(gameObject.acceleration, deltaTime);
}

void handleXBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.position.x + gameObject.size.x > bounds.maxX) {
        gameObject.position.x = bounds.maxX - gameObject.size.x;
        gameObject.velocity.x = -gameObject.velocity.x;
    } else if (gameObject.position.x < bounds.minX) {
        gameObject.position.x = bounds.minX;
        gameObject.velocity.x = -gameObject.velocity.x;
    }
}

void handleYBounds(GameObject& gameObject, const Bounds& bounds) {
    if (gameObject.position.y + gameObject.size.y > bounds.maxY) {
        gameObject.position.y = bounds.maxY - gameObject.size.y;
        gameObject.velocity.y = -gameObject.velocity.y;
    } else if (gameObject.position.y < bounds.minY) {
        gameObject.position.y = bounds.minY;
        gameObject.velocity.y = -gameObject.velocity.y;
    }
}

void boundarySystem(GameObject& gameObject, const Bounds& bounds) {
    handleXBounds(gameObject, bounds);
    handleYBounds(gameObject, bounds);
}

bool isOverlappingX(const GameObject& a, const GameObject& b) {
    float aLeft = a.position.x;
    float aRight = a.position.x + a.size.x;
    float bLeft = b.position.x;
    float bRight = b.position.x + b.size.x;

    return aLeft < bRight && aRight > bLeft;
}

bool isOverlappingY(const GameObject& a, const GameObject& b) {
    float aBottom = a.position.y;
    float aTop = a.position.y + a.size.y;
    float bBottom = b.position.y;
    float bTop = b.position.y + b.size.y;

    return aBottom < bTop && aTop > bBottom;
}

bool isColliding(const GameObject& a, const GameObject& b) {
    return isOverlappingX(a, b) && isOverlappingY(a, b);
}

void resolveCollisionX(GameObject& a, GameObject& b) {
    a.velocity.x = -a.velocity.x;
    b.velocity.x = -b.velocity.x;
}

void resolveCollisionY(GameObject& a, GameObject& b) {
    a.velocity.y = -a.velocity.y;
    b.velocity.y = -b.velocity.y;
}

void resolveCollision(GameObject& a, GameObject& b) {
    resolveCollisionX(a, b);
    resolveCollisionY(a, b);
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}
