#pragma once
#include <vector>
#include "Collision.h"


struct Engine {
    bool debugEnabled;
    bool isRunning;
    int frame;      // current frame count
    int maxFrames;  // configuration
    float deltaTime;
    Bounds worldBounds;
    int score;
    std::vector<GameObject> objects;

    Engine();
    void updateState();
    bool running() const;
    void input();
    void renderObjects() const;
    bool areObjectsColliding(int i, int j) const;
    void resolveObjectsCollision(int i, int j);
    void collisionSystemAllPairs();
    void physicsSystem();
    void movementSystem();
    void boundarySystem();
    void updateObjects();
    void update();
    void render() const;
    void run();
    void reset();
};
