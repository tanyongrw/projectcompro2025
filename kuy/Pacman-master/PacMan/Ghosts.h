﻿#ifndef GHOST_H
#define GHOST_H
#include "pacman.h" 

bool InMiddleTile(sf::Vector2f pos, sf::Vector2f prev, Dir dir);
std::vector<Dir> GetAvailableSquares(sf::Vector2f pos, Dir dir, bool home_tiles);
float Distance(int x, int y, int x1, int y1);
Dir GetShortestDir(const std::vector<Dir>& squares, const Ghost& ghost, sf::Vector2f target);
Dir GetOppositeTile(Ghost& ghost);

// ฟังก์ชันการไล่ล่าของผีสำหรับผู้เล่น 2 คน
sf::Vector2f BlinkyUpdate(Ghost& ghost);
sf::Vector2f PinkyUpdate(Ghost& ghost);
sf::Vector2f InkyUpdate(Ghost& ghost);
sf::Vector2f ClydeUpdate(Ghost& ghost);

// ฟังก์ชันพฤติกรรมของผี
bool PassedEntrence(Ghost& ghost);
void HouseUpdate(Ghost& ghost);
void UpdateDirection(std::vector<Dir> squares, Ghost& ghost);
void UpdateGhosts();

// ฟังก์ชันจัดการสถานะผี
void SetAllGhostState(TargetState new_state);
void SetGhostState(Ghost& ghost, TargetState new_state);

// ตำแหน่งเริ่มต้นและพฤติกรรมของผี
const float starting_x[4] = { 14, 14, 12, 16 };
const Dir enter_dir[4] = { UP, UP, LEFT, RIGHT };
const sf::Vector2f corners[4] = {
    {31, 0},
    {0, 0},
    {31, 31},
    {0, 31}
};

// จำนวนจุดที่ต้องกินก่อนผีออกจากบ้าน
const int dot_counters[4] = { 0, 0, 30, 60 };
const int global_dot_limit[4] = { 0, 7, 17, 32 };

const float PLAYER_TARGETING_SWITCH_TIME = 10.0f;
const float MIN_PLAYER_DISTANCE = 8.0f;
const float MAX_TARGETING_DISTANCE = 16.0f;

enum class GhostTargetMode {
    ALTERNATE_PLAYERS,
    NEAREST_PLAYER,
    FURTHEST_PLAYER,
    SPLIT_PLAYERS
};

#endif // !GHOST_H