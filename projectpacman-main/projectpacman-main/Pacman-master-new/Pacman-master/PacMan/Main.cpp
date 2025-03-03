#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <iostream>

#include "PlayerStats.h"
#include "Gameloop.h"
#include "Pacman.h" // ใช้ win_ratio จาก header แทน

sf::FloatRect calcView(const sf::Vector2f& windowSize, float pacRatio)
{
    sf::Vector2f viewSize = windowSize;
    sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);
    float ratio = viewSize.x / viewSize.y;

    if (ratio < pacRatio) {
        viewSize.y = viewSize.x / pacRatio;
        float vp_h = viewSize.y / windowSize.y;
        viewport.height = vp_h;
        viewport.top = (1.f - vp_h) / 2.f;
    }
    else if (ratio > pacRatio) {
        viewSize.x = viewSize.y * pacRatio;
        float vp_w = viewSize.x / windowSize.x;
        viewport.width = vp_w;
        viewport.left = (1.f - vp_w) / 2.f;
    }
    return viewport;
}

void OnResize(sf::RenderWindow& window, sf::Event& event)
{
    float h = static_cast<float>(event.size.height);
    float w = static_cast<float>(event.size.width);
    sf::View view = window.getView();
    view.setViewport(calcView({ w, h }, win_ratio));
    window.setView(view);
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned>(28.f * TSIZE * 2), static_cast<unsigned>(36.f * TSIZE * 2)), "PACMAN");
    window.setFramerateLimit(60);
    window.setView(sf::View({ 0, 0, 28.f * TSIZE, 36.f * TSIZE }));
    gState.window = &window;

    std::cout << "Enter your name: ";
    std::getline(std::cin, gState.playerName);

    loadPlayerStats(gState.playerName);  // โหลดข้อมูลของผู้เล่น
    gState.high_score = getHighScore(gState.playerName); // โหลด High Score

    OnStart();

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                savePlayerStats(gState.playerName, gState.game_score); // บันทึกคะแนนก่อนปิดเกม
                window.close();
                break;
            case sf::Event::Resized:
                OnResize(window, event);
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    savePlayerStats(gState.playerName, gState.game_score);
                    window.close();
                }
                break;
            }
        }
        elapsed = clock.restart();
        GameLoop(elapsed.asMilliseconds());
    }

    OnQuit();
    return 0;
}
