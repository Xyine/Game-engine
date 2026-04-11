#include <iostream>
#include <array>

const int objectCount = 2;

struct GameObject;

void updateSystem(GameObject& gameObject, float deltaTime);
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

    void print() const {
        std::cout << name << " position: ";
        position.print();
        std::cout << "\n";
    }

    void update(float deltaTime) { position.add(velocity, deltaTime); }
};

struct Engine {
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration
    float deltaTime;
    std::array<GameObject, objectCount> objects;
    
    Engine() : isRunning(true), frame(0), maxFrames(3), deltaTime(0.5f) {
        objects[0] = {"Player", {0.0f, 0.0f}, {1.0f, 0.0f}};
        objects[1] = {"Enemy", {10.0f, 5.0f}, {0.0f, 1.0f}};
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
            updateSystem(object, deltaTime);
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

void updateSystem(GameObject& gameObject, float deltaTime) {
    gameObject.update(deltaTime);
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}
