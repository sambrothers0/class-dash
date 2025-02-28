#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : Screen {
    public:
    LevelSelectScreen(SDL_Renderer* _renderer) : Screen(_renderer) {}

    virtual void draw() const;

    ~LevelSelectScreen() {}
};

#endif