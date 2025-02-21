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