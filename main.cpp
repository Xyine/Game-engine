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

    Vec2 add(const Vec2& other) const {
        return Vec2{x + other.x, y + other.y};
    }

    Vec2 scale(float scalar) const {
        return Vec2{x * scalar, y * scalar};
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
        std::cout << ", bounds: ";
        printBounds();
        std::cout << ", velocity: ";
        velocity.print();
        std::cout << ", acceleration: ";
        acceleration.print();
        std::cout << "\n";
    }

    void move(float deltaTime) {
        Vec2 deltaPosition = velocity.scale(deltaTime);
        position = position.add(deltaPosition); 
    }

    Vec2 center() const {
        return Vec2{position.x + size.x / 2.0f, position.y + size.y / 2.0f};
    }

    float left() const { return position.x; }

    float right() const { return position.x + size.x; }
    
    float bottom() const { return position.y; }
    
    float top() const { return position.y + size.y; }

    void printBounds() const {
        std::cout << "[left: " << left() 
            << ", right: " << right() 
            << ", bottom: " << bottom() 
            << ", top: " << top() 
            << "]";
    }   
};


void handleXBounds(GameObject& gameObject, const Bounds& bounds);
void handleYBounds(GameObject& gameObject, const Bounds& bounds);
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

    void renderObjects() const {
        for (const GameObject& object : objects) {
            renderSystem(object);
        }
    }

    bool firstTwoObjectsAreColliding() const {
        return areObjectsColliding(0, 1);
    }

    void handleCollisionBetweenFirstTwo() {
        resolveObjectsCollision(0, 1);
    }

    void collisionSystem() {
        std::cout << "Checking collision between " // TEMPORARY
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
            handleCollisionBetweenFirstTwo();
        }
    }

    bool areObjectsColliding(int i, int j) const {
        return isColliding(objects[i], objects[j]);
    }

    void resolveObjectsCollision(int i, int j) {
        resolveCollision(objects[i], objects[j]);
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
        boundarySystem();
    }

    void update() {
        input();
        std::cout << "World bounds: ";
        worldBounds.print();
        std::cout << "\n";
        std::cout << "Updating frame...\n";
        updateObjects();
        collisionSystem();
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

void resolveCollisionX(GameObject& a, GameObject& b) {
    a.velocity.x = -a.velocity.x;
    b.velocity.x = -b.velocity.x;
}

void resolveCollisionY(GameObject& a, GameObject& b) {
    a.velocity.y = -a.velocity.y;
    b.velocity.y = -b.velocity.y;
}

void resolveCollision(GameObject& a, GameObject& b) { // TEMPORARY
    resolveCollisionX(a, b);
    resolveCollisionY(a, b);
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}
