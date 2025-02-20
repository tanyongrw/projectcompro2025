#pragma once
#include <SFML/Graphics.hpp>

class Tile{
int sizeX;
int sizeY;
int posX;
int posY;
};

public:
    Tile(sf::Texture&, sf::Sprite, int, int, int xOfRect = 264, int sX = 32, int sY = 32);