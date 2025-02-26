#ifndef SOUND_H
#define SOUND_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class SoundManager {
public:
    SoundManager();

    void playMusic();
    void stopMusic();
    void setMusicVolume(float volume);

    void playStartSound();
    void playWinSound();
    void playLoseSound();

private:
    sf::Music music;
    sf::SoundBuffer startBuffer, winBuffer, loseBuffer;
    sf::Sound startSound, winSound, loseSound;
};

#endif
