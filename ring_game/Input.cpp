#include <SFML/Window/Keyboard.hpp>
#include "Input.h"

void updatePlayerInput(GameObject& player) {
    player.velocity = {0.f, 0.f};

    float speed = 3.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.velocity.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.velocity.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player.velocity.y = speed;
    }   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.velocity.y = -speed;
    }
}
