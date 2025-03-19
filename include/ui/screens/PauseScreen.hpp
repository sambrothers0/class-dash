#ifndef _PAUSE_SCREEN_H
#define _PAUSE_SCREEN_H

#include "ui/screens/Screen.hpp"
    
class PauseScreen : public Screen {
    public:
    PauseScreen(SDL_Renderer* _renderer) : Screen(_renderer) {}

    virtual void draw();

    virtual unsigned int handleEvent(SDL_Event& event);

    ~PauseScreen() {}
};

#endif