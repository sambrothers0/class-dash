#ifndef _GAME_H
#define _GAME_H

#include "SDL.h"

#include "PlayerView.hpp"
#include "GameLogic.hpp"

// Main Game class
class Game {
    private:
    SDL_Renderer* renderer;
    GameLogic gameLogic;
    PlayerView playerView;

    public:
    Game(SDL_Renderer* _renderer) : renderer(_renderer), gameLogic(GameLogic()), playerView(_renderer, gameLogic) {}

    void run();
};

#endif