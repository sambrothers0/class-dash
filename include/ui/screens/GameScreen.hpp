#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameScreen : public Screen {
    private:
    GameLogic& gameLogic;

    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic) : Screen(_renderer), gameLogic(_gameLogic) {}

    virtual void draw();

    virtual unsigned int handleEvent(SDL_Event&);

    ~GameScreen() {}
};

#endif