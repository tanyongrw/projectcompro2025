#include <SFML/graphics.hpp>
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
