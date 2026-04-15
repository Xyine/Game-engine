#pragma once
#include <iostream>
#include "Vec2.h"

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
