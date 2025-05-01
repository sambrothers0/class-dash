#ifndef _LEVEL_WIN_SCREEN_H
#define _LEVEL_WIN_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelWinScreen : public Screen {
    private:
    GameLogic& gameLogic;

    TTF_Font* font;

    int cursorPosition = 0;

    Text complete, next, quit;

    std::string backgroundPath = "../assets/visual/wren-bg.png";

    public:
    LevelWinScreen(SDL_Renderer* _renderer, TTF_Font* _font, GameLogic& _gameLogic);

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~LevelWinScreen() {}
};

#endif