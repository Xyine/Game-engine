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

    sf::CircleShape ball;
    ball.setFillColor(sf::Color::Blue);
    ball.setRadius(worldToScreenRadius(engine.objects[0], scale));

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

        engine.update();

        ball.setPosition(worldToScreenPosition(engine.objects[0], scale, windowHeight));

        window.clear();
        
        for (size_t i = 1; i < engine.objects.size(); i++) {
            if (!engine.objects[i].isBroken) {
                sf::CircleShape ring;
                ring.setRadius(worldToScreenRadius(engine.objects[i], scale));
                ring.setFillColor(sf::Color::Transparent);
                ring.setOutlineColor(sf::Color::Yellow);
                ring.setOutlineThickness(2.f);

                ring.setPosition(worldToScreenPosition(engine.objects[i], scale, windowHeight));

                window.draw(ring);
            }
        }

        window.draw(ball);
        window.display();
    }

    return 0;
}
