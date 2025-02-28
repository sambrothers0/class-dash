#ifndef _GAME_H
#define _GAME_H

#include "SDL.h"

// Main Game class
class Game {
    private:
    SDL_Renderer* renderer;

    bool isRunning = true;

    public:
    Game(SDL_Renderer* _renderer) : renderer(_renderer) {}

    void run();
};

#endif