#include <iostream>

struct GameObject {
    const char* name;
    int x;
    int y;
    int vx;
    int vy;
};

void input();
void update(GameObject& gameObject);
void render(const GameObject& gameObject);
void runEngine();

int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void update(GameObject& gameObject)  {
    std::cout << "Updating game...\n";

    gameObject.x += gameObject.vx;
    gameObject.y += gameObject.vy;
}

void render(const GameObject& gameObject) {
    std::cout << "Rendering frame...\n";
    std::cout << gameObject.name << " position: (" << gameObject.x << ", " << gameObject.y << ")\n";
}

void runEngine() {
    bool isRunning = true;
    int frame = 0;

    GameObject objects[2];
    objects[0] = {"Player", 0, 0, 1, 0};
    objects[1] = {"Enemy", 10, 5, 0, 1};

    while (isRunning) {
        input();

        for (int i = 0; i < 2; i++) {
            update(objects[i]);
        }

        for (int i = 0; i < 2; i++) {
            render(objects[i]);
        }
        
        std::cout << "---\n";

        frame++;

        if (frame >= 3) {
            isRunning = false;
        }
    }

    std::cout << "Engine stopped.\n";
}
