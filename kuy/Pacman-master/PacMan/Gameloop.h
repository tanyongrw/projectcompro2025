#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Pacman.h"
#include "Render.h"
#include "Ghosts.h"
#include "Player.h"
#include "Animate.h"
#include "Sound.h"

void OnStart();
void OnQuit();
void GameLoop(int ms_elapsed);

void Init();
void InitBoard();
void ResetGhostsAndPlayer();
void ResetBoard();
void SetupMenu();

void IncrementGhostHouse();
void CheckPelletCollision();
void CheckGhostCollision();
void UpdateWave(int ms_elapsed);
void UpdateEnergizerTime(int ms_elasped);
void CheckWin();

void CheckHighScore();
void LoadHighScore();
void SaveHighScore();

// game states
void MainLoop(int ms_elasped);
void GameStart(int ms_elasped);
void GameLose(int ms_elasped);
void GameWin(int ms_elasped);
void Menu(int ms_elapsed);

//*********
Player* player1;
Player* player2;
void SetPacManMenuFrame();
void StartPacManDeath(int player);
void SetPulseFrequency(int ms);
void PlayerMovement();
void AnimateUpdate(int ms_elapsed);
void PulseUpdate(int ms_elapsed);

extern GameState gState;


#endif // !GAMELOOP_H
