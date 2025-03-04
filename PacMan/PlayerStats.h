#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <map>
#include <string>

struct PlayerStats {
    std::string playerName;
    int score;
    int highScore;
};

void loadPlayerStats(const std::string& playerName);
void savePlayerStats(const std::string& playerName, int score); // ตรวจสอบว่าประกาศไว้
int getHighScore(const std::string& playerName);


#endif


