#ifndef _LEVEL_LOSE_SCREEN_H
#define _LEVEL_LOSE_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelLoseScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text title, restart, quit;

    public:
    LevelLoseScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
    Screen(_renderer), font(_font), 
        title(_renderer, _font, Vector2(512, 100), 50, { 0, 0, 0, 255 }, "Time's Up! You Lose"),
        restart(_renderer, _font, Vector2(512, 300), 40, { 0, 0, 0, 255 }, "Restart"),
        quit(_renderer, _font, Vector2(512, 400), 40, { 0, 0, 0, 255 }, "Quit")
    {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~LevelLoseScreen() {}
};

#endif