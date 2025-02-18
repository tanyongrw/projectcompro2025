#ifndef GHOST_H
#define GHOST_H
#include "Pacman.h"

// ฟังก์ชันพื้นฐาน
bool InMiddleTile(sf::Vector2f pos, sf::Vector2f prev, Dir dir);
std::vector<Dir> GetAvailableSquares(sf::Vector2f pos, Dir dir, bool home_tiles);
float Distance(int x, int y, int x1, int y1);
Dir GetShortestDir(const std::vector<Dir>& squares, const Ghost& ghost, sf::Vector2f target);
Dir GetOppositeTile(Ghost& ghost);

// ฟังก์ชันการไล่ล่าของผีสำหรับผู้เล่น 2 คน
sf::Vector2f BlinkyUpdate(Ghost& ghost);  // สลับเป้าหมายระหว่างผู้เล่น
sf::Vector2f PinkyUpdate(Ghost& ghost);   // ไล่ผู้เล่นที่ใกล้ที่สุด
sf::Vector2f InkyUpdate(Ghost& ghost);    // ใช้ผู้เล่นที่ไกลที่สุดในการคำนวณ
sf::Vector2f ClydeUpdate(Ghost& ghost);   // ไล่ผู้เล่นที่ใกล้หรือหนีถ้าใกล้เกินไป

// ฟังก์ชันพฤติกรรมของผี
bool PassedEntrence(Ghost& ghost);
void HouseUpdate(Ghost& ghost);
void UpdateDirection(std::vector<Dir> squares, Ghost& ghost);
void UpdateGhosts();

// ฟังก์ชันจัดการสถานะผี
void SetAllGhostState(TargetState new_state);
void SetGhostState(Ghost& ghost, TargetState new_state);

// ค่าคงที่สำหรับตำแหน่งเริ่มต้นและพฤติกรรมของผี
const float starting_x[4] = { 14, 14, 12, 16 };      // ตำแหน่ง X เริ่มต้นของผี
const Dir enter_dir[4] = { UP, UP, LEFT, RIGHT };    // ทิศทางการเข้าบ้าน
const sf::Vector2f corners[4] = {                    // มุมสำหรับโหมดกระจาย
    {31, 0},   // Blinky (มุมบนขวา)
    {0, 0},    // Pinky (มุมบนซ้าย)
    {31, 31},  // Inky (มุมล่างขวา)
    {0, 31}    // Clyde (มุมล่างซ้าย)
};

// จำนวนจุดที่ต้องกินก่อนผีออกจากบ้าน
const int dot_counters[4] = { 0, 0, 30, 60 };         // ตัวนับสำหรับแต่ละผี
const int global_dot_limit[4] = { 0, 7, 17, 32 };     // ขีดจำกัดตัวนับรวม

// ค่าคงที่ใหม่สำหรับโหมด 2 ผู้เล่น
const float PLAYER_TARGETING_SWITCH_TIME = 10.0f;      // เวลาก่อนผีจะเปลี่ยนเป้าหมาย
const float MIN_PLAYER_DISTANCE = 8.0f;                // ระยะห่างขั้นต่ำระหว่างผู้เล่น
const float MAX_TARGETING_DISTANCE = 16.0f;            // ระยะไล่ล่าสูงสุดของผี

// สถานะใหม่สำหรับการประสานงานของผีในโหมด 2 ผู้เล่น
enum class GhostTargetMode {
    ALTERNATE_PLAYERS,    //สลับระหว่างผู้เล่น
    NEAREST_PLAYER,      // ไล่ผู้เล่นที่ใกล้ที่สุด
    FURTHEST_PLAYER,     // ไล่ผู้เล่นที่ไกลที่สุด
    SPLIT_PLAYERS        // ผีแต่ละตัวแยกไล่ผู้เล่นคนละคน
};

#endif // !GHOST_H
