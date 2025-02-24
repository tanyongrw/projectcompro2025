#include "pacman.h"

// ��Ǩ�ͺ��ê��Ѻ��ᾧ
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

// ��Ǩ�ͺ��ê������ҧ������
bool PlayersCollision(sf::Vector2f pos1, sf::Vector2f pos2)
{
    // ��˹�������ҧ��鹵�ӷ������Ҫ��ѹ
    const float COLLISION_THRESHOLD = 0.8f;

    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    float distance = sqrt(dx * dx + dy * dy);

    return distance < COLLISION_THRESHOLD;
}

// ��Ǩ�ͺ��ê��Ѻ��ᾧ����Ѻ������
bool PlayerTileCollision(Dir dir, sf::Vector2f pos, int playerNumber)
{
    bool collided = false;
    char tile;

    // ��Ѻ��� offset ��������� (�Ҩ��ͧ��Ѻ�觵����Ҵ����Ф�)
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

// �Ѵ���˹觵���Ф���������觡�ҧ
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

// �ѧ��ѹ����Ѻ�¡����������ͪ��ѹ
void ResolvePLayerCollision(sf::Vector2f& pos1, sf::Vector2f& pos2, Dir dir1, Dir dir2)
{
    // ��Ҽ����蹪��ѹ ����¡�Ѻ���Ф��觢ͧ���зҧ���Ѻ�ѹ
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float distance = sqrt(dx * dx + dy * dy);

    if (distance < 0.8f) { // ���������ҧ���¡��Ң�Ҵ����Ф�
        float overlap = 0.8f - distance;
        float moveX = (dx / distance) * (overlap / 2);
        float moveY = (dy / distance) * (overlap / 2);

        // ��¼����� 1
        pos1.x -= moveX;
        pos1.y -= moveY;

        // ��¼����� 2
        pos2.x += moveX;
        pos2.y += moveY;
    }
}

// �ѧ��ѹ�������Ѻ��Ǩ�ͺ��ê�������
bool CheckAllCollisions(sf::Vector2f& pos1, sf::Vector2f& pos2, Dir dir1, Dir dir2)
{
    bool collision = false;

    // ��Ǩ�ͺ��ê��Ѻ��ᾧ
    if (PlayerTileCollision(dir1, pos1, 1) || PlayerTileCollision(dir2, pos2, 2)) {
        collision = true;
    }

    // ��Ǩ�ͺ��ê������ҧ������
    if (PlayersCollision(pos1, pos2)) {
        ResolvePLayerCollision(pos1, pos2, dir1, dir2);
        collision = true;
    }

    return collision;
}