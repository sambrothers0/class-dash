#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameScreen : public Screen {
    public:
    GameScreen(SDL_Renderer* _renderer) : Screen(_renderer) {}

    virtual void draw();

    ~GameScreen() {}
};

#endif