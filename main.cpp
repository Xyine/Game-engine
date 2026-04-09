#include <iostream>


void input();

void update();

void render();

void runEngine();


int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void update() {
    std::cout << "Updating game...\n";
}

void render() {
    std::cout << "Rendering frame...\n";
}

void runEngine() {
    for (int frame = 0; frame < 3; frame++) {
        input();
        update();
        render();
        std::cout << "---\n";
    }
}
