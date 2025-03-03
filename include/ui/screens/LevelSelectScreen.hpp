#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    public:
    LevelSelectScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic) : Screen(_renderer, _gameLogic) {}

    virtual void draw();

    ~LevelSelectScreen() {}
};

#endif