#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    private:

    TTF_Font* font;

    Text selectText;

    unsigned int levelsCompleted = 0;

    public:
    LevelSelectScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), selectText(
            _renderer,
            _font,
            Vector2(512, 650),
            35,
            SDL_Color { 0, 0, 0 },
            "Level Select"
        )  {}

    virtual void draw();

    virtual unsigned int handleEvent(SDL_Event& event);

    ~LevelSelectScreen() {}
};

#endif