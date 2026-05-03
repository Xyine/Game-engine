#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

sf::Vector2f worldToScreenPosition(const GameObject& object, float scale, float windowHeight);
sf::Vector2f worldToScreenSize(const GameObject& object, float scale);
float worldToScreenRadius(const GameObject& object, float scale);
