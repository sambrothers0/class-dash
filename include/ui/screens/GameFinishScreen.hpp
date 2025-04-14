#ifndef _GAME_FINISH_SCREEN_H
#define _GAME_FINISH_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameFinishScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text pause, resume, quit;

    public:
    GameFinishScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
    Screen(_renderer), font(_font), 
        pause(_renderer, _font, Vector2(512, 100), 50, { 0, 0, 0, 255 }, "Game Paused"),
        resume(_renderer, _font, Vector2(512, 300), 40, { 0, 0, 0, 255 }, "Resume"),
        quit(_renderer, _font, Vector2(512, 400), 40, { 0, 0, 0, 255 }, "Quit")
    {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~GameFinishScreen() {}
};

#endif