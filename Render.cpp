#include "Render.h"
#include "Animate.h"

static RenderItems RItems;
static Textures RTextures;

void InitRender()
{
    InitTextures();
    InitWalls();
    RItems.pellet_va.setPrimitiveType(sf::Quads);
    RItems.sprite_va.setPrimitiveType(sf::Quads);
    RItems.text_va.setPrimitiveType(sf::Quads);

    RItems.wall_map.setTexture(RTextures.wall_map_t);
    RItems.wall_map.setScale({ 0.5,0.5 });

    InitPellets();

    for (int i = 0; i < 4; i++)
    {
        RItems.ghosts[i].setTexture(RTextures.sprites);
        RItems.ghosts[i].setScale({ 0.5,0.5 });
        RItems.ghosts[i].setOrigin({ 16,16 });
    }

    for (int i = 0; i < 2; i++) {
        RItems.players[i].setTexture(RTextures.sprites);
        RItems.players[i].setScale({ 0.5,0.5 });
        RItems.players[i].setOrigin({ 15,15 });
    }

    RItems.float_score.setTexture(RTextures.sprites);
    RItems.float_score.setScale({ 0.5,0.5 });
    RItems.float_score.setOrigin({ 16,16 });
}


void DrawGameUI()
{
    ClearText();

    MakeText("P1 Score", 1, 0, { 255,255,255 });
    MakeText("P2 Score", 18, 0, { 255,255,255 });

    if (gState.game_state == GAMESTART)
        MakeText("Ready!", 11, 20, { 255,255,00 });
    else if (gState.game_state == GAMEOVER)
        MakeText("GAME  OVER", 9, 20, { 255,0,00 });

    std::string score1 = std::to_string(gState.game_score[0]);
    if (score1.size() == 1)
        score1.insert(score1.begin(), '0');
    MakeText(score1, 1, 1, { 255,255,255 });

    std::string score2 = std::to_string(gState.game_score[1]);
    if (score2.size() == 1)
        score2.insert(score2.begin(), '0');
    MakeText(score2, 18, 1, { 255,255,255 });

    RItems.players[0].setTextureRect({ 256,32,30,30 });
    RItems.players[1].setTextureRect({ 256,32,30,30 });

    for (int i = 0; i < gState.player_lives[0]; i++) {
        RItems.players[0].setPosition({ 24.f + 16 * i, 35 * TSIZE });
        gState.window->draw(RItems.players[0]);
    }

    for (int i = 0; i < gState.player_lives[1]; i++) {
        RItems.players[1].setPosition({ WINDOW_WIDTH - 40.f - 16 * i, 35 * TSIZE });
        gState.window->draw(RItems.players[1]);
    }
}

void DrawFrame()
{
    gState.window->clear(sf::Color::Black);
    DrawGameUI();

    if (RItems.pow_is_off != IsPulse()) {
        FlashPPellets();
        RItems.pow_is_off = !RItems.pow_is_off;
    }

    static bool white_texture = false;
    if (gState.game_state == GAMEWIN) {
        if (IsPulse() && !white_texture) {
            RItems.wall_map.setTexture(RTextures.wall_map_t_white);
            white_texture = true;
        }
        else if (!IsPulse() && white_texture) {
            RItems.wall_map.setTexture(RTextures.wall_map_t);
            white_texture = false;
        }
    }

    gState.window->draw(RItems.wall_map);
    gState.window->draw(RItems.text_va, &RTextures.font);
    gState.window->draw(RItems.pellet_va, &RTextures.pellets);

    for (int i = 0; i < 4; i++) {
        if (!gState.ghosts[i]->enable_draw)
            continue;
        RItems.ghosts[i].setPosition(gState.ghosts[i]->pos.x * TSIZE, gState.ghosts[i]->pos.y * TSIZE + YOFFSET);
        RItems.ghosts[i].setTextureRect(GetGhostFrame(gState.ghosts[i]->type, gState.ghosts[i]->target_state, gState.ghosts[i]->cur_dir));
        gState.window->draw(RItems.ghosts[i]);
    }

    for (int i = 0; i < 2; i++) {
        if (gState.players[i]->enable_draw) {
            RItems.players[i].setPosition(gState.players[i]->pos.x * TSIZE, gState.players[i]->pos.y * TSIZE + YOFFSET);
            RItems.players[i].setTextureRect(GetPacManFrame(gState.players[i]->cur_dir));
            gState.window->draw(RItems.players[i]);
        }
    }

    for (int i = 0; i < 2; i++) {
        if (gState.player_eat_ghost[i]) {
            RItems.float_score.setPosition(gState.players[i]->pos.x * TSIZE, gState.players[i]->pos.y * TSIZE + YOFFSET);
            RItems.float_score.setTextureRect({ (gState.ghosts_eaten_in_powerup[i] - 1) * 32,256,32,32 });
            gState.window->draw(RItems.float_score);
        }
    }

    gState.window->display();
}

void DrawMenuFrame()
{
    gState.window->clear(sf::Color::Black);
    DrawGameUI();
    if (IsPulse())
        MakeText("PRESS ENTER", 9, 25, { 255,255,255 });

    MakeText("P1 - ARROWS", 2, 8, { 255,255,0 });
    MakeText("P2 - WASD", 18, 8, { 0,255,255 });
    MakeText("-BLINKY", 9, 11, { 255,0,0 });
    MakeText("-PINKY", 9, 14, { 252,181,255 });
    MakeText("-INKY", 9, 17, { 0,255,255 });
    MakeText("-CLYDE", 9, 20, { 248,187,85 });

    for (int i = 0; i < 2; i++) {
        RItems.players[i].setPosition(gState.players[i]->pos.x * TSIZE, gState.players[i]->pos.y * TSIZE + YOFFSET);
        RItems.players[i].setTextureRect(GetPacManFrame(gState.players[i]->cur_dir));
        gState.window->draw(RItems.players[i]);
    }

    for (int i = 0; i < 4; i++) {
        RItems.ghosts[i].setPosition(gState.ghosts[i]->pos.x * TSIZE, gState.ghosts[i]->pos.y * TSIZE + YOFFSET);
        RItems.ghosts[i].setTextureRect(GetGhostFrame(gState.ghosts[i]->type, gState.ghosts[i]->target_state, gState.ghosts[i]->cur_dir));
        gState.window->draw(RItems.ghosts[i]);
    }

    gState.window->draw(RItems.text_va, &RTextures.font);
    gState.window->display();
}