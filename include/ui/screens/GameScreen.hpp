#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameScreen : public Screen {
    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic) : Screen(_renderer, _gameLogic) {}

    virtual void draw();

    virtual void handleEvent(SDL_Event&);

    ~GameScreen() {}
};

#endif