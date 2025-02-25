
#ifndef ANIMATE_H
#define ANIMATE_H

#include "pacman.h"
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation();
    
    void update(int ms_elapsed);
    void startPacManDeath(int player);
    void reset();
    void setPacManMenuFrame();
    
    static sf::IntRect getGhostFrame(GhostType type, TargetState state, Dir dir);
    static sf::IntRect getPacManFrame(Dir dir, int player);
    
    void pulseUpdate(int ms_elapsed);
    bool isPulse() const;
    void setPulseFrequency(int ms);

public:
    int pacman_frame;
    int pacman_timer;
    bool ascending;

    bool ghost_frame_2;
    int ghost_timer;

    int fright_flash;
    int energizer_timer;

    bool death_animation;

    int pulse;
    int pulse_timer;
    int pulse_limit;
};

#endif // ANIMATE_H
