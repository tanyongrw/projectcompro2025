#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "map.h"

void Map::generate(sf::RenderWindow& window, sf::Texture& tileTexture, int xOfRect)
{
    tilemap.clear();  

    std::ifstream openfile("Map2.txt");
    if (!openfile.is_open()) return;

    std::string line;
    int lineCount = 0;

    while (std::getline(openfile, line))
    {
        for (size_t column = 0; column < line.length(); column++)
        {
            if (line[column] == '1')
            {
                tilemap.emplace_back(tileTexture, column * 32, lineCount * 32, xOfRect);
            }
        }
        lineCount++;
    }

    for (auto& tile : tilemap)
    {
        tile.draw(window);
    }
}

std::vector<Tile> Map::getTilemap()
{
    return tilemap;
}

Tile::Tile(sf::Texture& texture, int x, int y, int xOfRect)
{
    posX = x;
    posY = y;

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(xOfRect, 0, 32, 32));
    sprite.setPosition(x, y);
}

int Tile::getPosY() const
{
    return posY;
}

int Tile::getPosX() const
{
    return posX;
}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
