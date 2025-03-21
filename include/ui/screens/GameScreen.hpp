#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameScreen : public Screen {
    private:
    GameLogic& gameLogic;
    TTF_Font* font;

    Text testText;

    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic, TTF_Font* _font) : 
        Screen(_renderer), gameLogic(_gameLogic), font(_font), testText(
            _renderer,
            _font,
            Vector2(100, 100),
            50,
            SDL_Color { 0, 255, 255 },
            "Test"
        ) {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event&);

    ~GameScreen() {}
};

#endif