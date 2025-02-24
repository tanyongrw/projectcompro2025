#ifndef RENDER_H
#define RENDER_H
#include "SFML/Graphics.hpp"
#include "pacman.h"
#include <map>

struct Textures
{
    sf::Texture pellets;
    sf::Texture sprites;
    sf::Texture wall_map_t;
    sf::Texture wall_map_t_white;
    sf::Texture font;
};

struct RenderItems
{
    sf::VertexArray pellet_va;
    sf::VertexArray sprite_va;
    sf::VertexArray wall_va;
    sf::Sprite wall_map;
    sf::Sprite float_score;
   
    sf::Sprite players[2];
    sf::Sprite ghosts[4];
    
    std::map<int, int> pellet_va_indicies;
   
    int pow_indicies[4];
    sf::VertexArray text_va;
    bool pow_is_off = false;

    
    bool player_eat_ghost[2];  
    int ghost_eaten_score[2];  
};


const int font_width = 14;
const int NUM_PLAYERS = 2;
const sf::FloatRect pel_r = { 0,0,16,16 };
const sf::FloatRect pow_r = { 16,0,16,16 };

void InitRender();
void InitWalls();
void InitTextures();
void InitPellets();
void ResetPellets();
void RemovePellet(int x, int y);
void MakeQuad(sf::VertexArray& va, float x, float y, int w, int h,
    sf::Color color = { 255,255,255 }, sf::FloatRect tex_rect = { 0,0,0,0 });


void DrawGameUI();
void DrawFrame();
void DrawPlayerScore(int player_index, int x, int y);  
void DrawPlayerLives(int player_index);  

void FlashPPellets();
void ResetPPelletFlash();
void DrawMenuFrame();


void ClearText();
void MakeText(std::string string, int x, int y, sf::Color f_color);

#endif // !RENDER_H