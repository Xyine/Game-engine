#include <iostream>
#include <array>

const int objectCount = 2;

struct Vec2 {
    int x;
    int y;
};

struct GameObject {
    const char* name;
    Vec2 position;
    Vec2 velocity;
};

struct Engine {
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration   
    std::array<GameObject, objectCount> objects;
};

void input();
void updateSystem(GameObject& gameObject);
void renderSystem(const GameObject& gameObject);
void initializeEngine(Engine& engine);
void updateObjects(Engine& engine);
void renderObjects(const Engine& engine);
void processFrame(Engine& engine);
void updateEngineState(Engine& engine);
void runEngine();

int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void updateSystem(GameObject& gameObject) {
    std::cout << "Updating " << gameObject.name << "...\n";

    gameObject.position.x += gameObject.velocity.x;
    gameObject.position.y += gameObject.velocity.y;
}

void renderSystem(const GameObject& gameObject) {
    std::cout << "Rendering " << gameObject.name << "...\n";
    std::cout << gameObject.name << " position: (" << gameObject.position.x << ", " << gameObject.position.y << ")\n";
}

void initializeEngine(Engine& engine) {
    engine.isRunning = true;
    engine.frame = 0;
    engine.maxFrames = 3;

    engine.objects[0] = {"Player", 0, 0, 1, 0};
    engine.objects[1] = {"Enemy", 10, 5, 0, 1};
}

void updateObjects(Engine& engine) {
    for (GameObject& object : engine.objects) {
        updateSystem(object);
    }
}

void renderObjects(const Engine& engine) {
    for (const GameObject& object : engine.objects) {
        renderSystem(object);
    }
}

void processFrame(Engine& engine) {
    input();
    updateObjects(engine);
    renderObjects(engine);
    std::cout << "---\n";
}

void updateEngineState(Engine& engine) {
    engine.frame++;

    if (engine.frame >= engine.maxFrames) {
        engine.isRunning = false;
    }
}

void runEngine() {
    Engine engine;

    initializeEngine(engine);

    while (engine.isRunning) {
        processFrame(engine);
        updateEngineState(engine);
    }

    std::cout << "Engine stopped.\n";
}
