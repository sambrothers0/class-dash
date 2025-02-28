#ifndef _PLAYER_VIEW_H
#define _PLAYER_VIEW_H

#include "SDL.h"

#include <memory>

#include "ui/screens/Screen.hpp"

class PlayerView {
    private:
    SDL_Renderer* renderer;

    // Pointer to the current screen, it needs a pointer because Screen is an abstract class
    // This needs to be set in the constructor
    std::unique_ptr<Screen> screen;

    public:
    PlayerView(SDL_Renderer* _renderer);

    void draw();

    // Handles an SDL event
    void handleEvent(SDL_Event& event);

    // Switches to the title screen
    void switchToTitleScreen();

    // Switches to the game screen
    void switchToGameScreen();
};

#endif