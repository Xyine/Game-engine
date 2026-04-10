#include <iostream>

const int objectCount = 2;

struct GameObject {
    const char* name;
    int x;
    int y;
    int vx;
    int vy;
};

struct Engine {
    bool isRunning;
    int frame;
    GameObject objects[objectCount];
};

void input();
void update(GameObject& gameObject);
void render(const GameObject& gameObject);
void processFrame(Engine& engine);
void runEngine();

int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void update(GameObject& gameObject)  {
    std::cout << "Updating " << gameObject.name << "...\n";

    gameObject.x += gameObject.vx;
    gameObject.y += gameObject.vy;
}

void render(const GameObject& gameObject) {
    std::cout << "Rendering " << gameObject.name << "...\n";
    std::cout << gameObject.name << " position: (" << gameObject.x << ", " << gameObject.y << ")\n";
}

void processFrame(Engine& engine) {
    input();

    for (int i = 0; i < objectCount; i++) {
        update(engine.objects[i]);
    }

    for (int i = 0; i < objectCount; i++) {
        render(engine.objects[i]);
    }

    std::cout << "---\n";
}

void runEngine() {
    Engine engine;
    engine.isRunning = true;
    engine.frame = 0;

    engine.objects[0] = {"Player", 0, 0, 1, 0};
    engine.objects[1] = {"Enemy", 10, 5, 0, 1};

    while (engine.isRunning) {
        processFrame(engine);

        engine.frame++;

        if (engine.frame >= 3) {
            engine.isRunning = false;
        }
    }

    std::cout << "Engine stopped.\n";
}
