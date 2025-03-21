#ifndef _PAUSE_SCREEN_H
#define _PAUSE_SCREEN_H

#include "ui/screens/Screen.hpp"
    
class PauseScreen : public Screen {
    private:

    TTF_Font* font;

    Text pauseText;

    public:
    PauseScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), pauseText(
            _renderer,
            _font,
            Vector2(512, 650),
            35,
            SDL_Color { 0, 0, 0 },
            "Paused, Press Esc to Resume, Q to Quit"
        )  {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~PauseScreen() {}
};

#endif