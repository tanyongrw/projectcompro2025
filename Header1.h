#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
private:
    sf::Sprite sprite;
    int posX, posY;

public:
    Tile(sf::Texture& texture, int x, int y, int xOfRect = 264, int size = 32);
    int getPosX() const;
    int getPosY() const;
    void draw(sf::RenderWindow& window) const;
};

class Map {
private:
    std::vector<Tile> tilemap;

public:
    void generate(sf::RenderWindow& window, sf::Texture& tileTexture, int xOfRect = 264);
    const std::vector<Tile>& getTilemap() const;
};
