#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    private:
    unsigned int levelsCompleted = 0;

    public:
    LevelSelectScreen(SDL_Renderer* _renderer) : Screen(_renderer) {}

    virtual void draw();

    virtual unsigned int handleEvent(SDL_Event& event);

    ~LevelSelectScreen() {}
};

#endif