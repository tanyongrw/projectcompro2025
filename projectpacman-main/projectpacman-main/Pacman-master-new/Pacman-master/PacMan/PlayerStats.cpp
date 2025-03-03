#include "PlayerStats.h"
#include <iostream>
#include <fstream>
#include <map>

std::map<std::string, PlayerStats> playerData;

void loadPlayerStats(const std::string& playerName) {
    std::ifstream inFile("player_stats.txt");
    if (!inFile.is_open()) {
        std::cout << "Error: Unable to open file for loading stats.\n";
        return;
    }

    std::string name;
    int score, highScore;
    while (inFile >> name >> score >> highScore) {
        playerData[name] = { name, score, highScore };
    }
    inFile.close();

    if (playerData.find(playerName) == playerData.end()) {
        playerData[playerName] = { playerName, 0, 0 };  // ถ้าไม่มี ให้สร้างใหม่
    }
}

void savePlayerStats(const std::string& playerName, int score) {
    playerData[playerName].score = score;
    if (score > playerData[playerName].highScore) {
        playerData[playerName].highScore = score;
    }

    std::ofstream outFile("player_stats.txt");
    if (!outFile.is_open()) {
        std::cout << "Error: Unable to open file for saving stats.\n";
        return;
    }

    for (const auto& entry : playerData) {
        outFile << entry.second.playerName << " "
            << entry.second.score << " "
            << entry.second.highScore << "\n";
    }
    outFile.close();
}

int getHighScore(const std::string& playerName) {
    if (playerData.find(playerName) != playerData.end()) {
        return playerData[playerName].highScore;
    }
    return 0;
}
int getgame_score(const std::string& playerName) {
    if (playerData.find(playerName) != playerData.end()) {
        return playerData[playerName].score;
    }
    return 0;
}