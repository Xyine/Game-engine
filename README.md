# 2D Physics Game Engine (C++ / SFML)

A simple 2D game engine built from scratch in C++ using SFML for rendering.

This project focuses on implementing core game engine systems manually, including physics, collision detection, and object management, without relying on external physics libraries.

## Features

- Custom 2D physics system (velocity, acceleration, delta time)
- Axis-Aligned Bounding Box (AABB) collision detection
- Custom Circle vs Ring collision system
- Collision resolution with velocity reflection
- Dynamic object system using `std::vector`
- World-to-screen coordinate transformation
- Real-time rendering using SFML

## Demo Gameplay

- A ball starts at the center of the screen
- 100 concentric rings surround the ball
- Gravity pulls the ball downward
- Each time the ball hits a ring:
  - it bounces realistically
  - the ring breaks and disappears
- The ball continues until all rings are destroyed


## Technical Highlights

### Physics System
- Explicit Euler integration:
  ```cpp
  velocity += acceleration * deltaTime;
  position += velocity * deltaTime;
  ```

### Collision System
- AABB for rectangles
- Custom radial collision for circle vs ring:
    - Distance-based detection
    - Normal vector computation

    - Reflection formula:
    ```cpp
    v' = v - 2 * dot(v, n) * n
    ```

### Engine Architecture
- Modular systems:
    - Physics
    - Movement
    - Collision
    - Rendering
- Data-oriented structure using GameObject
- Scalable object management with std::vector

## Tech Stack

C++
SFML (Simple and Fast Multimedia Library)

## Build & Run

### Requirements

C++17 or later
SFML installed

### Build (example with g++)

You can use the implement make:

```bash
make
```

or the classic:

```bash
g++ *.cpp -o engine -lsfml-graphics -lsfml-window -lsfml-system
```

### Run

```bash
./engine
```

## Purpose

This project was built to deepen understanding of:

- Game engine architecture
- Physics simulation
- Collision detection and resolution
- Real-time systems in C++

## Future Improvements

- Spatial partitioning (QuadTree / Grid)
- Rotations and angular physics
- Particle system for ring breaking
- Basic ECS (Entity Component System)
