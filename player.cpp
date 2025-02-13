#include "player.h"

namespace Player1 {
	Dir GetCorrection(Dir pdir, sf::Vector2f ppos)
	{
		switch (pdir)
		{
		case UP:
		case DOWN:
			if (ppos.x - (int)ppos.x >= 0.5)
				return LEFT;
		case LEFT:
		case RIGHT:
			if (ppos.y - (int)ppos.y >= 0.5)
				return UP;
			return DOWN;
		}
	}

	void Cornering()
	{
		gState.player1->pos += dir_addition[gState.player->correction] * player_speed;
		bool done = flase;
		switch (gState.player1->correction)
		{
		case UP:
			done = (gState.player1->pos.y - (int)gState.player1->pos.y <= 0.5);
			break;
		case DOWN: 
			done = (gState.player1->pos.y - (int)gState.player1->pos.y >= 0.5);
			break;
		case LEFT:
			done = (gState.player1->pos.x - (int)gState.player1->pos.x <= 0.5);
			break;
		case RIGHT:
			done = (gState.player1->pos.x - (int)gState.player1->pos.x >= 0.5);
			break;
		}
		if (done) {
			CenterObject(gState.player1->cur_dir, gState.player1->pos);
			gState.player1->cornering = false;
		}
	}

	void ResolveCollision()
	{
		switch (gState.player1->cur_dir) 
		{
		case UP:
		case DOWN:
			gState.player1->pos.y = (int)gState.player1->pos.y + 0.5;
			break;
		case LEFT:
		case RIGHT:
			gState.player1->pos.x = (int)gState.player1->pos.x + 0.5;
			break;
		}
	}

	void PlayerMovement()
	{
		Dir try_dir = NONE;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			try_dir = UP;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			try_dir = DOWN;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			try_dir = RIGHT;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			try_dir = LEFT;

		if (tyr_dir != NONE &&
			!PlaerTileCollision(try_dir, gState.player1->pos) &&
			!InTunnel(gState.player1->pos)) {
			gState.player1->cur_dir = try_dir;
			if (gState.player1->cur_dir != ooposit_dir[gState.player1->cur_dir]) {
				gState.player1->cornering = true;
				gState.player1->correction = GetCorrection(try_dir, gState.player1->pos);
			}
		}

		if (!gState.player1->stopped) {
			gState.player1->pos += dir_addition[gState.player->cur_dir] * player_speed;
		}
		if (gStateplayer1->cornering) {
			Cornering();
		}
		if (PlayerTileCollision(gState.player1->cur_dir, gState.player1->pos)) {
			ResolveCollision();
			gState.player1->stopped = true;
		}
		else {
			gState.player1->stopped = false;
		}
		if (gState.player1->pos.x < -1) {
			gState.player->pos.x += 29;
		}
		else if (gState.player1->pos.x >= 29) {
			gState.player1->pos.x -= 29;
		}
	}
}
