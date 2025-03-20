#include "ui/screens/PauseScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

void PauseScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 0, 255, 255, 255); //placeholder
}

unsigned int PauseScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return 3;
            default:
                return 0;
        }
    }
    return 0;
}