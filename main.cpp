#include <SFML/Graphics.hpp>
#include "Engine.h"

int main()
{
    Engine engine;

    float scale = 100.f;
    float windowHeight = 600.f;

    sf::RenderWindow window(sf::VideoMode(800, windowHeight), "Engine + SFML");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape player;
    player.setSize({
        engine.objects[0].size.x * scale,
        engine.objects[0].size.y * scale
    });

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        engine.deltaTime = deltaTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        engine.objects[0].velocity = {0.f, 0.f};

        float speed = 3.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            engine.objects[0].velocity.x = -speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            engine.objects[0].velocity.x = speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            engine.objects[0].velocity.y = speed;
        }   
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            engine.objects[0].velocity.y = -speed;
        }
        
        engine.updateObjects();

        player.setPosition(
            engine.objects[0].position.x * scale,
            windowHeight - (engine.objects[0].position.y + engine.objects[0].size.y) * scale
        );

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}