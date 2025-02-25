#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "pacman.h"
#include "Render.h"
#include "Ghosts.h"
#include "player.h"
#include "Animate.h"
#include "Music1.wav"
#include "startsound"
#include "winsound"
#include "losesound"

void OnStart();
void OnQuit();
void GameLoop(int ms_elapsed);


void Init();
void InitBoard();
void ResetGhostsAndPlayers(); 
void ResetBoard();
void SetupMenu();


void IncrementGhostHouse();
void CheckPelletCollision();  
void CheckGhostCollision();   
void UpdateWave(int ms_elapsed);
void UpdateEnergizerTime(int ms_elapsed);  
void CheckWin();

// Score handling
void CheckHighScore();  
void LoadHighScore();  
void SaveHighScore();  

// Player specific functions
void HandlePlayerInput();  
void UpdatePlayer(int ms_elapsed); 
void HandlePlayerCollisions(); 

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
