#ifndef _SCREEN_H
#define _SCREEN_H

#include "SDL.h"

#include "GameLogic.hpp"

// Abstract class
class Screen {
    protected:
    // Reference to the renderer
    SDL_Renderer* renderer;

    public:
    Screen(SDL_Renderer* _renderer) : renderer(_renderer) {}

    // Draws the screen using the renderer
    virtual void draw() = 0;

    // Handles events
    virtual void handleEvent(SDL_Event& event) {}

    // Pure virtual destructor
    virtual ~Screen() = 0;
};

#endif