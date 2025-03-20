#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

#include "ui/screens/Screen.hpp"
    
class TitleScreen : public Screen {
    public:
    TitleScreen(SDL_Renderer* _renderer) : Screen(_renderer) {}

    virtual void draw();

    virtual unsigned int handleEvent(SDL_Event& event);

    ~TitleScreen() {}
};

#endif