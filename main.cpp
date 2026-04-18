#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Render.h"
#include "Input.h"

int main()
{
    Engine engine;
    engine.debugEnabled = false;
    
    float scale = 100.f;
    float windowHeight = 600.f;

    sf::RenderWindow window(sf::VideoMode(800, windowHeight), "Engine + SFML");
    window.setVerticalSyncEnabled(true);

    sf::RectangleShape player;
    player.setFillColor(sf::Color::Green);
    player.setSize(worldToScreenSize(engine.objects[0], scale));

    sf::RectangleShape enemy;
    enemy.setFillColor(sf::Color::Red);
    enemy.setSize(worldToScreenSize(engine.objects[1], scale));

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

        updatePlayerInput(engine.objects[0]);

        engine.update();
        
        player.setPosition(worldToScreenPosition(engine.objects[0], scale, windowHeight));
        enemy.setPosition(worldToScreenPosition(engine.objects[1], scale, windowHeight));

        window.clear();
        window.draw(player);
        window.draw(enemy);
        window.display();
    }

    return 0;
}
