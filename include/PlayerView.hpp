#ifndef _PLAYER_VIEW_H
#define _PLAYER_VIEW_H

#include "SDL.h"

#include <memory>

#include "ui/screens/Screen.hpp"
#include "ui/screens/TitleScreen.hpp"

class PlayerView {
    private:
    SDL_Renderer* renderer;

    // Pointer to the current screen, it needs a pointer because Screen is an abstract class
    std::unique_ptr<Screen> screen;

    public:
    PlayerView(SDL_Renderer* _renderer) : renderer(_renderer) {
        switchToTitleScreen();
    }

    void draw();

    // Handles an SDL event
    void handleEvent(SDL_Event& event);

    // Switches to the title screen
    void switchToTitleScreen() {
        screen = std::make_unique<TitleScreen>(TitleScreen(renderer));
    }
};

#endif