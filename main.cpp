#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <time.h>
#include "Gameloop.h"

sf::FloatRect calSplitScreenView(const sf::Vector2f& windowSize, float pacRatio, bool isLeftView)
{
	sf::Vector2f viewSize = windowSize;
	sf::FloatRect viewport(0.f, 0.f, 0.5f, 1.f);

	if(isLeftView){
		viewport.left = 0.f;
	}
	else {
		viewport.left = 0.5f;
	}

	float ratio = (viewSize.x * 0.5f) / viewSize.y;

	if (ratio < pacRatio){
		viewSize.y = (viewSize.x + 0.5f) / pacRatio;
		float vp_h = viewSize.y / windowSize.y;
		viewport.height = vp_h;
		viewport.top = (1.f - vp_h) / 2.f;
	}

	else if (ratio > pacRatio){
		viewSize.x = viewSize.y * pacRatio;
		float vp_w = (viewSize.x * 0.5f) / windowSize.x;
		viewport.width = vp_w;
		viewport.left = isLeftView ? (0.5f - vp_w) / 2.f : 0.5f + (0, 5f - vp_w) / 2.f;

	}

	return viewport;
}


void OnResize(sf::RenderWindow& window, sf::Event& event)
{
	float h = event.size.height;
	float w = event.size.width;


	sf::View player1View = sf::View({ 0, 0, 28.f * TSIZE, 36.f * TSIZE });
	sf::View player2View = sf::View({ 0, 0, 28.f * TSIZE, 36.f * TSIZE });

	player1View.setViewport(calSplitScreenView({ w,h }, win_ratio, true));
	player2View.setViewport(calSplitScreenView({ w,h }, win_ratio, false));


	gState.playerView = player1View;
	gState.player2View = player2View;
}

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(28.s * TSIZE * 4, 36.f * TSIZE * 2), "PACMAN - 2 PLAYERS");
	window.setFramerateLimit(60);

	sf::View player1View({ 0, 0, 28.f * TSIZE, 36.f * TSIZE });
	sf::View player2View({ 0, 0, 28.f * TSIZE, 36.f * TSIZE });


	player1View.setViewport(calSplitScreenView({ window.getSize().x * 1.f, window.getSize().y * 1.f }, win_ratio, true));
	player2View.setViewport(calSplitScreenView({ window.getSize().x * 1.f, window.getSize().y * 1.f }, win_ratio, false));

	gState.window = &window;
	gState.player1View = player1View;
	gState.player2View = player2View;

	OnStart();
	sf::Clock clock;
	sf::Time elapsed;


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					OnResize(window, event);
					break;
				case sf::Event::KeyPressed:
					switch (event.key.code) {
						case sf::Keyboard::Escape:
							window.close();
							break;
					}
					
			}
		}

		elapsed = clock.restart();

		window.clear();

		window.setView(gState.player1View);
		GameLoop(elapsed.asMilliseconds(), 1);

		window.setView(gState.player2View);
		GameLoop(elapsed.asMilliseconds(), 2);

		window.display();
	}

	OnQuit();
	return 0;
}
