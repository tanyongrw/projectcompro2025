#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "pacman.h"
#include "Render.h"
#include "Ghosts.h"
#include "player.h"
#include "Animate.h"
#include "Music1.wav"

void OnStart();
void OnQuit();
void GameLoop(int ms_elapsed);
void Init();
void InitBoard();

// Reset functions
void ResetGhostsAndPlayers(); 
void ResetBoard();
void SetupMenu();

// Game mechanics
void IncrementGhostHouse();
void CheckPelletCollision(int player_index);  
void CheckGhostCollision(int player_index);   
void UpdateWave(int ms_elapsed);
void UpdateEnergizerTime(int ms_elapsed, int player_index);  
void CheckWin();

// Score handling
void CheckHighScore(int player_index);  
void LoadHighScores();  
void SaveHighScores();  

// Player specific functions
void HandlePlayerInput(int player_index);  
void UpdatePlayer(int player_index, int ms_elapsed); 
void HandlePlayerCollisions(int player_index); 

// Multiplayer specific functions
void CheckPlayerCollisions(); 
void DetermineWinner();      
void UpdatePlayerScores();    

// Game states
void MainLoop(int ms_elapsed);
void GameStart(int ms_elapsed);
void GameLose(int ms_elapsed);
void GameWin(int ms_elapsed);
void Menu(int ms_elapsed);

// Multiplayer game states
void PlayerVictoryScreen(int winning_player);  
void PlayerDeathSequence(int player_index);   

#endif // !GAMELOOP_H