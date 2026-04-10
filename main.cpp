#include <iostream>
#include <array>

const int objectCount = 2;

struct Engine;
struct GameObject;

void input();
void updateSystem(GameObject& gameObject);
void renderSystem(const GameObject& gameObject);

struct Vec2 {
    int x;
    int y;

    void add(const Vec2& other) {
        x += other.x;
        y += other.y;
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

    void update() { position.add(velocity); }
};

struct Engine {
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration   
    std::array<GameObject, objectCount> objects;

    void initialize() {
        isRunning = true;
        frame = 0;
        maxFrames = 3;

        objects[0] = {"Player", {0, 0}, {1, 0}};
        objects[1] = {"Enemy", {10, 5}, {0, 1}};
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

    void updateObjects() {
        for (GameObject& object : objects) {
            updateSystem(object);
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
};

void runEngine();

int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void updateSystem(GameObject& gameObject) {
    gameObject.update();
}

void renderSystem(const GameObject& gameObject) {
    gameObject.print();
}

void runEngine() {
    Engine engine;

    engine.initialize();

    while (engine.running()) {
        engine.processFrame();
        engine.updateState();
    }

    std::cout << "Engine stopped.\n";
}
