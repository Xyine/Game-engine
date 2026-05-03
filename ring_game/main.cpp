#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "Render.h"
#include "RingGameSetup.h"

enum GameState {
    MENU,
    GAME,
    PAUSE
};

void drawGame(
    sf::RenderWindow& window,
    const Engine& engine,
    sf::CircleShape& ball,
    const sf::Text& reset,
    const sf::Text& menu,
    const sf::Text& pause,
    const sf::Text& score,
    float scale,
    float windowHeight
);

int main()
{
    GameState state = MENU;
    GameState previous_state = MENU;
    Engine engine;
    int scoreValue = 0;
    setupRingGameObjects(engine);
    engine.debugEnabled = false;
    
    const float scale = 100.f;
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        return -1;
    }

    sf::Text reset("Reset", font, 20);
    reset.setFillColor(sf::Color::White);
    reset.setPosition(40, 100);

    sf::Text menu("Menu", font, 20);
    menu.setFillColor(sf::Color::White);
    menu.setPosition(40, 20);

    sf::Text pause("Pause", font, 20);
    pause.setFillColor(sf::Color::White);
    pause.setPosition(40, 60);

    sf::Text play("PLAY", font, 40);
    play.setFillColor(sf::Color::White);
    play.setPosition(250, 250);

    sf::Text quit("QUIT", font, 40);
    quit.setFillColor(sf::Color::White);
    quit.setPosition(450, 250);

    sf::Text score(std::to_string(scoreValue), font, 30);
    score.setFillColor(sf::Color::White);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Engine + SFML");
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

        score.setString(std::to_string(scoreValue));
        sf::FloatRect bounds = score.getLocalBounds();
        score.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
        score.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

        if (state == MENU) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {

                    sf::Vector2f mousePos(
                        event.mouseButton.x,
                        event.mouseButton.y
                    );

                    if (play.getGlobalBounds().contains(mousePos)) {
                        state = (previous_state == PAUSE) ? PAUSE : GAME;
                    }
                    if (quit.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                }
            }
            window.clear();
            window.draw(play);
            window.draw(quit);
        } else {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed) {

                    sf::Vector2f mousePos(
                        event.mouseButton.x,
                        event.mouseButton.y
                    );

                    if (reset.getGlobalBounds().contains(mousePos)) {
                        engine.reset();
                        engine.debugEnabled = false;
                        setupRingGameObjects(engine);
                    }

                    if (menu.getGlobalBounds().contains(mousePos)) {
                        previous_state = state;
                        state = MENU;
                    }
                    if (pause.getGlobalBounds().contains(mousePos)) {
                        previous_state = state;
                        state = (state == GAME) ? PAUSE : GAME;
                    }
                }
            }

            if (state == GAME) {
                engine.update();
                scoreValue += engine.lastCollisionCount;
            }

            window.clear();
            drawGame(window, engine, ball, reset, menu, pause, score, scale, static_cast<float>(windowHeight));
        }
        window.display();
    }

    return 0;
}

void drawGame(
    sf::RenderWindow& window,
    const Engine& engine,
    sf::CircleShape& ball,
    const sf::Text& reset,
    const sf::Text& menu,
    const sf::Text& pause,
    const sf::Text& score,
    float scale,
    float windowHeight
) {
    ball.setPosition(worldToScreenPosition(engine.objects[0], scale, windowHeight));

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

    window.draw(reset);
    window.draw(menu);
    window.draw(pause);
    window.draw(score);
    window.draw(ball);
}
