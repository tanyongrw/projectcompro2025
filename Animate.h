#ifndef ANIMATE_H
#define ANIMATE_H

#include "Pacman.h"

struct Animation
{
    int pacman_frame = 0;
    int pacman_timer = 0;
    bool assending = true;

    bool ghost_frame_2 = false;
    int ghost_timer = 0;

    int fright_flash = 0;
    int energizer_timer = 0;

    bool death_animation = false;

    int pulse = 1; 
    int pulse_timer = 0;
    int pulse_limit = 200;
};

static Animation animate;
static Animation animate2; 

void AnimateUpdate(int ms_elapsed);
void StartPacManDeath(int player);
void ResetAnimation();
void SetPacManMenuFrame();

sf::IntRect GetGhostFrame(GhostType type, TargetState state, Dir dir);
sf::IntRect GetPacManFrame(Dir dir, int player);
void PulseUpdate(int ms_elapsed);
bool IsPulse();
void SetPulseFrequency(int ms);

#endif // ANIMATE_H
