#include <iostream>
#include <array>

const int objectCount = 2;

struct GameObject;

void movementSystem(GameObject& gameObject, float deltaTime);
void physicsSystem(GameObject& gameObject, float deltaTime);
void boundarySystem(GameObject& gameObject, float minX, float maxX, float minY, float maxY);
void renderSystem(const GameObject& gameObject);

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
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    void print() const {
        std::cout << name << " position: ";
        position.print();
        std::cout << ", velocity: ";
        velocity.print();
        std::cout << ", acceleration: ";
        acceleration.print();
        std::cout << "\n";
    }

    void move(float deltaTime) { position.add(velocity, deltaTime); }
};

struct Engine {
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration
    float deltaTime;
    float minX;
    float maxX;
    float minY;
    float maxY;
    std::array<GameObject, objectCount> objects;
    
    Engine() : isRunning(true), frame(0), maxFrames(3), deltaTime(0.5f), minX(0.0f), maxX(3.0f), minY(0.0f), maxY(6.0f) {
        objects[0] = {"Player", {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 0.0f}};
        objects[1] = {"Enemy", {10.0f, 5.0f}, {0.0f, 1.0f}, {0.0f, 0.0f}};
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
            boundarySystem(object, minX, maxX, minY, maxY);
        }
    }

    void renderObjects() const {
        for (const GameObject& object : objects) {
            renderSystem(object);
        }
    }

    void processFrame() {
        input();
        std::cout << "Updating frame...\n";
        updateObjects();
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

void boundarySystem(GameObject& gameObject, float minX, float maxX, float minY, float maxY) {
    if (gameObject.position.x > maxX) {
        gameObject.position.x = maxX;
        gameObject.velocity.x = -gameObject.velocity.x;
    } else if (gameObject.position.x < minX) {
        gameObject.position.x = minX;
        gameObject.velocity.x = -gameObject.velocity.x;
    }
    if (gameObject.position.y > maxY) {
        gameObject.position.y = maxY;
        gameObject.velocity.y = -gameObject.velocity.y;
    } else if (gameObject.position.y < minY) {
        gameObject.position.y = minY;
        gameObject.velocity.y = -gameObject.velocity.y;
    }
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}
