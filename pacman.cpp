#include "pacman.h"

// ตรวจสอบการชนกับกำแพง
bool TileCollision(sf::Vector2f pos, bool home_tiles)
{
    bool collided = false;
    char tile = GetTile(pos.x, pos.y);

    if (tile == '|')
        collided = true;
    if (!home_tiles && tile == '-')
        collided = true;

    return collided;
}

// ตรวจสอบการชนระหว่างผู้เล่น
bool PlayersCollision(sf::Vector2f pos1, sf::Vector2f pos2)
{
    // กำหนดระยะห่างขั้นต่ำที่ถือว่าชนกัน
    const float COLLISION_THRESHOLD = 0.8f;

    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float distance = sqrt(dx * dx + dy * dy);

    return distance < COLLISION_THRESHOLD;
}

// ตรวจสอบการชนกับกำแพงสำหรับผู้เล่น
bool PlayerTileCollision(Dir dir, sf::Vector2f pos, int playerNumber)
{
    bool collided = false;
    char tile;

    // ปรับค่า offset ตามผู้เล่น (อาจต้องปรับแต่งตามขนาดตัวละคร)
    float offset = (playerNumber == 1) ? 0.51f : 0.51f;

    switch (dir)
    {
    case UP:
        tile = GetTile(pos.x, pos.y - offset);
        break;
    case DOWN:
        tile = GetTile(pos.x, pos.y + offset);
        break;
    case LEFT:
        tile = GetTile(pos.x - offset, pos.y);
        break;
    case RIGHT:
        tile = GetTile(pos.x + offset, pos.y);
        break;
    }

    if (tile == '|' || tile == '-')
        collided = true;

    return collided;
}

// จัดตำแหน่งตัวละครให้อยู่กึ่งกลาง
void CenterObject(Dir dir, sf::Vector2f& pos)
{
    switch (dir)
    {
    case UP:
    case DOWN:
        pos.x = (int)pos.x + 0.5;
        break;
    case LEFT:
    case RIGHT:
        pos.y = (int)pos.y + 0.5;
        break;
    }
}

// ฟังก์ชันสำหรับแยกผู้เล่นเมื่อชนกัน
void ResolvePLayerCollision(sf::Vector2f& pos1, sf::Vector2f& pos2, Dir dir1, Dir dir2)
{
    // ถ้าผู้เล่นชนกัน ให้ถอยกลับคนละครึ่งของระยะทางที่ทับกัน
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < 0.8f) { // ถ้าระยะห่างน้อยกว่าขนาดตัวละคร
        float overlap = 0.8f - distance;
        float moveX = (dx / distance) * (overlap / 2);
        float moveY = (dy / distance) * (overlap / 2);

        // ถอยผู้เล่น 1
        pos1.x -= moveX;
        pos1.y -= moveY;

        // ถอยผู้เล่น 2
        pos2.x += moveX;
        pos2.y += moveY;
    }
}

// ฟังก์ชันรวมสำหรับตรวจสอบการชนทั้งหมด
bool CheckAllCollisions(sf::Vector2f& pos1, sf::Vector2f& pos2, Dir dir1, Dir dir2)
{
    bool collision = false;

    // ตรวจสอบการชนกับกำแพง
    if (PlayerTileCollision(dir1, pos1, 1) || PlayerTileCollision(dir2, pos2, 2)) {
        collision = true;
    }

    // ตรวจสอบการชนระหว่างผู้เล่น
    if (PlayersCollision(pos1, pos2)) {
        ResolvePLayerCollision(pos1, pos2, dir1, dir2);
        collision = true;
    }

    return collision;
}