#include "Sound.h"

SoundManager::SoundManager() {
    // Load music
    if (!music.openFromFile("Sounds/Music1.wav")) {
        std::cout << "OMG1: Failed to load Music1.wav" << std::endl;
    }
    music.setVolume(33);
    music.setLoop(true);

    // Load start sound
    if (!startBuffer.loadFromFile("Sounds/startsound.wav")) {
        std::cout << "OMG2: Failed to load startsound.wav" << std::endl;
    }
    startSound.setBuffer(startBuffer);
    startSound.setVolume(44);

    // Load win sound
    if (!winBuffer.loadFromFile("Sounds/winsound.wav")) {
        std::cout << "OMG3: Failed to load winsound.wav" << std::endl;
    }
    winSound.setBuffer(winBuffer);
    winSound.setVolume(44);

    // Load lose sound
    if (!loseBuffer.loadFromFile("Sounds/deadsound.wav")) {
        std::cout << "OMG4: Failed to load deadsound.wav" << std::endl;
    }
    loseSound.setBuffer(loseBuffer);
    loseSound.setVolume(44);
}

void SoundManager::playMusic() {
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}

void SoundManager::setMusicVolume(float volume) {
    music.setVolume(volume);
}

void SoundManager::playStartSound() {
    startSound.play();
}

void SoundManager::playWinSound() {
    winSound.play();
}

void SoundManager::playLoseSound() {
    loseSound.play();
}
