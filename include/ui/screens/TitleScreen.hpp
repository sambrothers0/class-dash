#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

#include "ui/screens/Screen.hpp"
#include <iostream>
    
class TitleScreen : public Screen {
    private:

    TTF_Font* font;

    Text titleText, startText, howToPlayText;

    public:
    TitleScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 
        titleText(_renderer, _font, Vector2(512, 200), 50, {0, 0, 0, 255}, "Class Dash"),
        startText(_renderer, _font, Vector2(512, 500), 40, {0, 0, 0, 255}, "Start"),
        howToPlayText(_renderer, _font, Vector2(512, 600), 30, {0, 0, 0, 255}, "How to Play")
    {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~TitleScreen() {}
};

#endif