#ifndef _GAME_H
#define _GAME_H

#include "SDL.h"

#include "PlayerView.hpp"
#include "GameLogic.hpp"

// Main Game class
class Game {
    private:
    SDL_Renderer* renderer;
    PlayerView playerView;
    GameLogic gameLogic;

    public:
    Game(SDL_Renderer* _renderer) : renderer(_renderer), playerView(
        PlayerView(_renderer)
    ), gameLogic(GameLogic()) {}

    void run();
};

#endif