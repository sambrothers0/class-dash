#ifndef _SCREEN_H
#define _SCREEN_H

#include "SDL.h"

#include "GameLogic.hpp"
#include "ui/Text.hpp"
#include "ui/screens/ScreenType.hpp"

// Abstract class
class Screen {
    protected:
    // Reference to the renderer
    SDL_Renderer* renderer;

    public:
    Screen(SDL_Renderer* _renderer) : renderer(_renderer) {}

    // Draws the screen using the renderer
    virtual void draw() = 0;

    // Handles events, return value indicates if the screen needs to be switched
    virtual ScreenType handleEvent(SDL_Event& event) { return ScreenType::KEEP; }

    // Pure virtual destructor
    virtual ~Screen() = 0;
};

#endif