#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

#include "ui/screens/Screen.hpp"
    
class TitleScreen : public Screen {
    private:

    TTF_Font* font;

    Text playText;

    public:
    TitleScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), playText(
            _renderer,
            _font,
            Vector2(512, 650),
            35,
            SDL_Color { 0, 0, 0 },
            "Press Enter to Play, Q to Quit"
        )  {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~TitleScreen() {}
};

#endif