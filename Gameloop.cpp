#include "Gameloop.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector> 0
GameState gState;

void OnStart()
{
	Init();
	LoadHighScore();
}
void OnQuit()
{
	SaveHighScore();
}

void LoadHighScore()
{
	std::ifstream infile;
	std::stringstream ss;
	std::string line;
	int hs = 0;
	infile.open("highscore.txt");
	if (!infile) {
		gState.high_score = 0;
		return;
	}
	getline(infile, line);
	ss << line;
	ss >> hs;

	gState.high_score = hs;
}
void SaveHighScore()
{
	std::ofstream outfile("highscore.txt");
	if (!outfile.is_open())
		printf("Cant open file!");

	outfile << gState.high_score;
	outfile.close();
}
void InitBoard()
{
	std::string line;
	std::ifstream infile("Map.txt");
	if (!infile)
		return;
	while (getline(infile, line))
	{
		gState.board.push_back(line);
	}

	infile.close();

}
void Init() //*
{
	// player1
	Player* pl1 = new Player(); 
	pl1->cur_dir = UP;
	pl1->pos = { 14,23.5 }; //position
	pl1->stopped = true;
	gState.player.push_back(pl1); // เพิ่มผู้เล่นลงใน vector

	// player2
	Player* pl2 = new Player();
	pl2->cur_dir = UP;
	pl2->pos = { 16,23.5 }; //position
	pl2->stopped = true;
	gState.player.push_back(pl2);



	// Ghosts init

	Ghost* temp = new Ghost();
	temp->type = RED;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = PINK;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = BLUE;
	gState.ghosts.push_back(temp);

	temp = new Ghost();
	temp->type = ORANGE;
	gState.ghosts.push_back(temp);

	InitBoard();
	InitRender();
	ResetGhostsAndPlayer();

	InitSounds();

	SetupMenu();
	gState.game_state = MENU;
	gState.pause_time = 2000;
}
void ResetGhostsAndPlayer() //*
{
	Ghost* temp = gState.ghosts[0];
	temp->pos = { 14, 11.5 };
	temp->cur_dir = LEFT;
	temp->target_state = CORNER;
	temp->in_house = false;
	temp->move_speed = ghost_speed;
	//temp->dot_counter = 0;
	temp->enable_draw = true;

	temp = gState.ghosts[1];
	temp->pos = { 14, 14.5 };
	temp->cur_dir = UP;
	temp->target_state = HOMEBASE;
	temp->in_house = true;
	temp->move_speed = inhome_speed;
	//temp->dot_counter = 0;
	temp->enable_draw = true;

	temp = gState.ghosts[2];
	temp->pos = { 12, 14.5 };
	temp->cur_dir = DOWN;
	temp->target_state = HOMEBASE;
	temp->in_house = true;
	temp->move_speed = inhome_speed;
	//temp->dot_counter = 0;
	temp->enable_draw = true;

	temp = gState.ghosts[3];
	temp->pos = { 16, 14.5 };
	temp->cur_dir = DOWN;
	temp->target_state = HOMEBASE;
	temp->in_house = true;
	temp->move_speed = inhome_speed;
	//temp->dot_counter = 0;
	temp->enable_draw = true;

	// Reset player1 
	gState.player1->cur_dir = UP;
	gState.player1->pos = { 14,23.5 }; //positionให้ตรงvoid Init()
	gState.player1->stopped = true;
	gState.player1->enable_draw = true;

	// Reset player2
	gState.player2->cur_dir = UP;
	gState.player2->pos = { 16,23.5 }; //positionให้ตรงvoid Init()
	gState.player2->stopped = true;
	gState.player2->enable_draw = true;

	ResetAnimation();
	gState.energizer_time = 0;
	gState.wave_counter = 0;
	gState.wave_time = 0;

	ResetPPelletFlash();

	if (!gState.first_life)
		gState.using_global_counter = true;

	gState.global_dot_counter = 0;
}
void ResetBoard()
{
	gState.board.clear();
	InitBoard();

	gState.pellets_left = 244;

	gState.first_life = true;
	gState.using_global_counter = false;
	for (int i = 0; i < 4; i++)
		gState.ghosts[i]->dot_counter = 0;
}

void IncrementGhostHouse()
{
	Ghost* first_ghost = nullptr;
	// using global counter, increment it
	if (gState.using_global_counter) {
		gState.global_dot_counter++;
	}
	for (int i = 0; i < 4; i++) {
		if (gState.ghosts[i]->target_state == HOMEBASE) {
			first_ghost = gState.ghosts[i];
			break;
		}
	}
	if (first_ghost == nullptr) {
		// no more ghosts in house, switch back to local counters
		if (gState.using_global_counter) {
			gState.using_global_counter = false;
		}
	}
	// if not using global and ghost is in house, use local counter
	else if (!gState.using_global_counter) {
		first_ghost->dot_counter++;
	}
}
void CheckPelletCollision() //*
{
	// ตรวจสอบการชนของ Player 1
	char tile = GetTile(gState.player1->pos.x, gState.player1->pos.y);
	bool collided = false;
	if (tile == '.') {
		collided = true;
		// play sound
		gState.game_score += 10;
		PlayMunch();
	}
	else if (tile == 'o') {
		collided = true;
		gState.game_score += 50;
		gState.energizer_time = fright_time * 1000;

		gState.ghosts_eaten_in_powerup = 0;

		SetAllGhostState(FRIGHTENED);
	}

	if (collided) {
		RemovePellet(gState.player1->pos.x, gState.player1->pos.y);
		SetTile(gState.player1->pos.x, gState.player1->pos.y, ' ');
		IncrementGhostHouse();
		gState.pellet_eaten = true;
		gState.pellets_left--;
	}

	// ตรวจสอบการชนของ Player 2
	collided = false;
	tile = GetTile(gState.player2->pos.x, gState.player2->pos.y);
	if (tile == '.') {
		collided = true;
		// play sound
		gState.game_score += 10;
		PlayMunch();
	}
	else if (tile == 'o') {
		collided = true;
		gState.game_score += 50;
		gState.energizer_time = fright_time * 1000;
		gState.ghosts_eaten_in_powerup = 0;
		SetAllGhostState(FRIGHTENED);
	}

	if (collided) {
		RemovePellet(gState.player2->pos.x, gState.player2->pos.y);
		SetTile(gState.player2->pos.x, gState.player2->pos.y, ' ');
		IncrementGhostHouse();
		gState.pellet_eaten = true;
		gState.pellets_left--;
	}
}
void CheckGhostCollision() //*
{
	int px1 = (int)gState.player1->pos.x;
	int py1 = (int)gState.player1->pos.y;

	int px2 = (int)gState.player2->pos.x;
	int py2 = (int)gState.player2->pos.y;

	// เช็คการชนของ Player 1
	for (int i = 0; i < 4; i++) {
		if ((int)gState.ghosts[i]->pos.x == px1 && (int)gState.ghosts[i]->pos.y == py1) {
			if (gState.ghosts[i]->target_state == FRIGHTENED) {
				SetGhostState(*gState.ghosts[i], GOHOME);
				gState.recent_eaten = gState.ghosts[i];
				gState.ghosts_eaten_in_powerup++;
				gState.game_score += (pow(2, gState.ghosts_eaten_in_powerup) * 100);

				gState.player_eat_ghost = true;
				gState.pause_time = 500;

				gState.ghosts[i]->enable_draw = false;
				gState.player1->enable_draw = false;

				PlayEatGhost();
			}
			else if (gState.ghosts[i]->target_state != GOHOME) {
				gState.game_state = GAMELOSE;
				gState.pause_time = 2000;
				gState.player_lives -= 1;
				gState.first_life = false;
				StartPacManDeath();
				StopSounds();
				PlayDeathSound();
				printf("RESET\n");
			}
		}
	}
	// เช็คการชนของ Player 2
	for (int i = 0; i < 4; i++) {
		if ((int)gState.ghosts[i]->pos.x == px2 && (int)gState.ghosts[i]->pos.y == py2) {
			if (gState.ghosts[i]->target_state == FRIGHTENED) {
				SetGhostState(*gState.ghosts[i], GOHOME);
				gState.recent_eaten = gState.ghosts[i];
				gState.ghosts_eaten_in_powerup++;
				gState.game_score += (pow(2, gState.ghosts_eaten_in_powerup) * 100);

				gState.player_eat_ghost = true;
				gState.pause_time = 500;

				gState.ghosts[i]->enable_draw = false;
				gState.player2->enable_draw = false;

				PlayEatGhost();
			}
			else if (gState.ghosts[i]->target_state != GOHOME) {
				gState.game_state = GAMELOSE;
				gState.pause_time = 2000;
				gState.player_lives -= 1;
				gState.first_life = false;
				StartPacManDeath();
				StopSounds();
				PlayDeathSound();
				printf("RESET\n");
			}
		}
	}
}
void UpdateWave(int ms_elapsed) 
{
	// indefinte chase mode
	if (gState.wave_counter >= 7)
		return;

	gState.wave_time += ms_elapsed;
	if (gState.wave_time / 1000 >= wave_times[gState.wave_counter]) {
		gState.wave_counter++;
		printf("New wave\n");
		if (gState.energizer_time <= 0)
			SetAllGhostState(GetGlobalTarget());
		gState.wave_time = 0;
	}

}
void UpdateEnergizerTime(int ms_elasped)
{
	if (gState.energizer_time <= 0)
		return;

	gState.energizer_time -= ms_elasped;
	if (gState.energizer_time <= 0) {
		SetAllGhostState(GetGlobalTarget());
	}
}
void CheckHighScore()
{
	if (gState.game_score > gState.high_score)
		gState.high_score = gState.game_score;
}
void CheckWin()//*
{
	if (gState.player1->pellets_left <= 0 || gState.player2->pellets_left <= 0) {
		gState.game_state = GAMEWIN;

		//ซ่อนผี
		for (int i = 0; i < 4; i++) {
			gState.ghosts[i]->enable_draw = false;
		}
		//หยุfผู้เล่นทั้ง2
		gState.player1->stopped = true;
		gState.player2->stopped = true;

		gState.pause_time = 2000;
		StopSounds();
		SetPulseFrequency(200);
	}
}
void MainLoop(int ms_elapsed)
{
	if (gState.player_eat_ghost) {
		gState.pause_time -= ms_elapsed;
		if (gState.pause_time < 0) {
			gState.recent_eaten->enable_draw = true;
			gState.player->enable_draw = true;
			gState.player_eat_ghost = false;
		}
		DrawFrame();

		return;
	}

	// pacman doesnt move for one frame if he eats a pellet
	// from the original game
	if (!gState.pellet_eaten)
		PlayerMovement();
	else gState.pellet_eaten = false;
	// check collision first so less funny stuff
	CheckGhostCollision();
	CheckPelletCollision();
	UpdateGhosts();
	UpdateWave(ms_elapsed);
	UpdateEnergizerTime(ms_elapsed);
	CheckHighScore();
	CheckWin();
	UpdateGameSounds(ms_elapsed);

	AnimateUpdate(ms_elapsed);
	DrawFrame();
}
void GameStart(int ms_elasped)
{
	//startsound maka
	soundManager.playStartSound();
	
	gState.pause_time -= ms_elasped;
	if (gState.pause_time <= 0) {
		gState.game_state = MAINLOOP;
		SetPulseFrequency(150);
	}

	DrawFrame();
}
void GameLose(int ms_elapsed) //*
{
	//lose soufn NAJa
	soundManager.playLoseSound();
	
	gState.pause_time -= ms_elapsed;
	if (gState.players1->lives < 0 && gState.players2->lives < 0) {
		if (gState.player_lives < 0) {
			gState.game_state = GAMEOVER;
			gState.pause_time = 5000;
			for (int i = 0; i < 4; i++)
				gState.ghosts[i]->enable_draw = false;
			gState.player1->enable_draw = false;
			gState.player2->enable_draw = false;
		}
		else {
			gState.game_state = GAMESTART;
			gState.pause_time = 2000;

			ResetGhostsAndPlayer();
		}
	}
	UpdateGameSounds(ms_elapsed);
	AnimateUpdate(ms_elapsed);
	DrawFrame();
}
void GameWin(int ms_elapsed)
{
	//winsound NAJA
	soundManager.playWinSound();
	
	gState.pause_time -= ms_elapsed;
	if (gState.pause_time <= 0) {
		ResetPellets();
		ResetBoard();
		ResetGhostsAndPlayer();
		gState.pause_time = 2000;
		gState.game_state = GAMESTART;
	}
	AnimateUpdate(ms_elapsed);
	DrawFrame();
}
void SetupMenu()//*
{
	for (int i = 0; i < 4; i++) {
		gState.ghosts[i]->enable_draw = true;
		gState.ghosts[i]->pos = { 6,5.5f + i * 3.f };
		gState.ghosts[i]->cur_dir = RIGHT;
		gState.ghosts[i]->target_state = CHASE;
		gState.ghosts[i]->in_house = false;
	}
	//player1 setting
	gState.player1->enable_draw = true;
	gState.player1->pos = { 6,17.5f }; //position
	gState.player1->cur_dir = RIGHT;

	//player2 setting
	gState.player2->enable_draw = true;
	gState.player2->pos = { 8,17.5f };
	gState.player2->cur_dir = RIGHT;

	SetPacManMenuFrame();
	SetPulseFrequency(200);
}
void Menu(int ms_elapsed)//*
{
	PulseUpdate(ms_elapsed);
	DrawMenuFrame();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		ResetPellets();
		ResetBoard();
		ResetGhostsAndPlayer();
		gState.game_score = 0;
		gState.player1_lives = 3; //*
		gState.player2_lives = 3; //*
		PlayGameStart();
		gState.pause_time = 4000;
		gState.game_state = GAMESTART;
	}
}
void GameLoop(int ms_elapsed)
{
	switch (gState.game_state)
	{
	case MAINLOOP:
		MainLoop(ms_elapsed);
		break;
	case GAMESTART:
		GameStart(ms_elapsed);
		break;
	case GAMELOSE:
		GameLose(ms_elapsed);
		break;
	case GAMEOVER:
		gState.pause_time -= ms_elapsed;
		if (gState.pause_time < 0) {
			SetupMenu();
			gState.game_state = MENU;
		}
		//gState.game_state = MENU;
		DrawFrame();
		break;
	case GAMEWIN:
		GameWin(ms_elapsed);
		break;
	case MENU:
		Menu(ms_elapsed);
		break;
	}
}
