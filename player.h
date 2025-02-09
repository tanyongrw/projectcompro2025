#include <SFML/graphics.hpp>
#include <random>
#include <time.h>
#ifndef PLAYER_H
#define PLAYER_H

#include "Pacman.h"

namespace Player1 {
	Dir GetCorrection(Dir pdir, sf::Vector2f ppos);
	void Correcing();
	void ResolveCollision();
	void PlayerMovement();
}
// ฟังก์ชันสำหรับผู้เล่นคนที่1

namespace Player2 {
	Dir GetCorrection(Dir pdir, sf::Vertor2f ppos);
	void Correcing();
	void ResolveCollision();
	void PlayerMovement();
}
// ฟังก์ชันสำหรับผู้เล่นคนที่2

struct PlayerStats {};
{
	int score;
	int lives;
	bool isAlive;
};
// ฟังก์ชันสำหรับทั้งสองคน

void IntializePlayers();
void UpdatePlayerState();
bool CheckPlayerCollision();
void HandPLayerInteraction();


#endif // !PLAYER_H



 
