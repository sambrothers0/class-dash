#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

#include "ui/screens/Screen.hpp"
#include <iostream>
    
class TitleScreen : public Screen {
    private:

    TTF_Font* font;

    Text titleText, startText, howToPlayText;

    SDL_Texture* background = nullptr;

    public:
    TitleScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 
        titleText(_renderer, _font, Vector2(512, 130), 50, {0, 0, 0, 255}, "Class Dash"),
        startText(_renderer, _font, Vector2(512, 585), 40, {0, 0, 0, 255}, "Start"),
        howToPlayText(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, "How to Play")
    {
}

    void init();

    virtual void draw();

    void drawBackground(SDL_Renderer* renderer, SDL_Texture* texture);

    virtual ScreenType handleEvent(SDL_Event& event);

    ~TitleScreen();
};

#endif