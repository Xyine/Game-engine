#include <iostream>

enum class Direction {
    Left,
    Right,
    Up,
    Down
};

struct GameObject {
    int x;
    int y;
};

void input();
void update(GameObject& gameObject, Direction direction) ;
void render(const GameObject& gameObject);
void runEngine();

int main() {
    runEngine();
    return 0;
}

void input() {
    std::cout << "Handling input...\n";
}

void update(GameObject& gameObject, Direction direction)  {
    std::cout << "Updating game...\n";

    switch (direction) {
        case Direction::Left:
            gameObject.x--;
            break;
        case Direction::Right:
            gameObject.x++;
            break;
        case Direction::Up:
            gameObject.y++;
            break;
        case Direction::Down:
            gameObject.y--;
            break;
        default:
            break;
    }
}

void render(const GameObject& gameObject) {
    std::cout << "Rendering frame...\n";
    std::cout << "Object position: (" << gameObject.x << ", " << gameObject.y << ")\n";
}

void runEngine() {
    bool isRunning = true;
    int frame = 0;

    GameObject gameObject{0, 0};
    Direction order[3] = {Direction::Right, Direction::Right, Direction::Up};

    while (isRunning) {
        input();
        Direction direction = order[frame];
        update(gameObject, direction);
        render(gameObject);
        std::cout << "---\n";

        frame++;

        if (frame >= 3) {
            isRunning = false;
        }
    }

    std::cout << "Engine stopped.\n";
}
