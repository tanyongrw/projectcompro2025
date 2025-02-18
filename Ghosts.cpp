#include "Ghosts.h"

// ตรวจสอบว่าผีอยู่กลางช่องหรือไม่
bool InMiddleTile(sf::Vector2f pos, sf::Vector2f prev, Dir dir)
{
    // ตรวจสอบว่าตำแหน่งปัจจุบันและก่อนหน้าอยู่ในช่องเดียวกันหรือไม่
    if ((int)pos.x != (int)prev.x || (int)pos.y != (int)prev.y)
        return false;
    float x = pos.x - (int)pos.x;
    float y = pos.y - (int)pos.y;
    float px = prev.x - (int)prev.x;
    float py = prev.y - (int)prev.y;

    switch (dir)
    {
    case UP:
    case DOWN:
        return std::min(y, py) <= 0.5 && std::max(y, py) >= 0.5;
    case LEFT:
    case RIGHT:
        return std::min(x, px) <= 0.5 && std::max(x, px) >= 0.5;
    }
    return false;
}

// ฟังก์ชันอัปเดตการเคลื่อนที่ของผีแต่ละตัวสำหรับ 2 ผู้เล่น
sf::Vector2f BlinkyUpdate(Ghost& ghost)
{
    // ผีแดง (Blinky) จะสลับไล่ระหว่างผู้เล่น 1 และ 2
    static bool target_player_one = true;
    target_player_one = !target_player_one;
    return target_player_one ? gState.player1->pos : gState.player2->pos;
}

sf::Vector2f PinkyUpdate(Ghost& ghost)
{
    // ผีชมพู (Pinky) จะไล่ไปข้างหน้าผู้เล่นที่อยู่ใกล้ที่สุด 4 ช่อง
    float dist1 = Distance(ghost.pos.x, ghost.pos.y, gState.player1->pos.x, gState.player1->pos.y);
    float dist2 = Distance(ghost.pos.x, ghost.pos.y, gState.player2->pos.x, gState.player2->pos.y);

    Player* target_player = (dist1 < dist2) ? gState.player1 : gState.player2;
    return target_player->pos + dir_addition[target_player->cur_dir] * 4;
}

sf::Vector2f InkyUpdate(Ghost& ghost)
{
    // ผีฟ้า (Inky) ใช้ตำแหน่งของ Blinky คำนวณระยะห่างจากผู้เล่นที่ไกลที่สุด
    sf::Vector2f blinky_pos = gState.ghosts[RED]->pos;
    float dist1 = Distance(blinky_pos.x, blinky_pos.y, gState.player1->pos.x, gState.player1->pos.y);
    float dist2 = Distance(blinky_pos.x, blinky_pos.y, gState.player2->pos.x, gState.player2->pos.y);

    Player* target_player = (dist1 > dist2) ? gState.player1 : gState.player2;
    sf::Vector2f target = target_player->pos + dir_addition[target_player->cur_dir] * 2;
    sf::Vector2f offset = blinky_pos - target;
    return target + offset * -1;
}

sf::Vector2f ClydeUpdate(Ghost& ghost)
{
    // ผีส้ม (Clyde) จะไล่ผู้เล่นที่ใกล้ที่สุดถ้าอยู่ไกลเกิน 8 ช่อง ไม่งั้นจะหนีไปมุม
    float dist1 = Distance(ghost.pos.x, ghost.pos.y, gState.player1->pos.x, gState.player1->pos.y);
    float dist2 = Distance(ghost.pos.x, ghost.pos.y, gState.player2->pos.x, gState.player2->pos.y);

    if (std::min(dist1, dist2) < 64) { // น้อยกว่า 8 ช่อง (8^2 = 64)
        return sf::Vector2f(0, 31); // หนีไปมุมล่างซ้าย
    }

    return (dist1 < dist2) ? gState.player1->pos : gState.player2->pos;
}

// อัปเดตทิศทางการเคลื่อนที่ของผี
void UpdateDirection(std::vector<Dir> squares, Ghost& ghost)
{
    sf::Vector2f target;
    bool update_dir = false;

    if (squares.size() == 1) {
        ghost.cur_dir = squares.at(0);
    }

    switch (ghost.target_state)
    {
    case FRIGHTENED: // โหมดกลัว (ผีสีน้ำเงิน)
        ghost.cur_dir = squares.at(rand() % (squares.size()));
        break;
    case GOHOME: // กลับบ้าน
        target = sf::Vector2f(14, 11.5);
        update_dir = true;
        break;
    case CHASE: // โหมดไล่ล่า
        switch (ghost.type)
        {
        case RED:
            target = BlinkyUpdate(ghost);
            break;
        case PINK:
            target = PinkyUpdate(ghost);
            break;
        case BLUE:
            target = InkyUpdate(ghost);
            break;
        case ORANGE:
            target = ClydeUpdate(ghost);
            break;
        }
        update_dir = true;
        break;
    case CORNER: // ไปที่มุม
        target = corners[ghost.type];
        update_dir = true;
        break;
    }

    if (update_dir)
        ghost.cur_dir = GetShortestDir(squares, ghost, target);

    CenterObject(ghost.cur_dir, ghost.pos);
}
