#pragma once
#include "GameObject.h"
#include "Bounds.h"

void handleXBounds(GameObject& gameObject, const Bounds& bounds);
void handleYBounds(GameObject& gameObject, const Bounds& bounds);
bool isOverlappingX(const GameObject& a, const GameObject& b);
bool isOverlappingY(const GameObject& a, const GameObject& b);
bool isColliding(const GameObject& a, const GameObject& b);
float overlapX(const GameObject& a, const GameObject& b);
float overlapY(const GameObject& a, const GameObject& b);
void separateObjectsX(GameObject& a, GameObject& b);
void separateObjectsY(GameObject& a, GameObject& b);
void resolveCollisionX(GameObject& a, GameObject& b);
void resolveCollisionY(GameObject& a, GameObject& b);
void resolveCollision(GameObject& a, GameObject& b);
