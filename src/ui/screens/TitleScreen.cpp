#include "ui/screens/TitleScreen.hpp"

#include "SDL2_gfxPrimitives.h"
#include <iostream>

void TitleScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    playText.draw();
}

unsigned int TitleScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                return 2;
            case SDLK_RETURN:
                return 2;
            default:
                return 0;
        }
    }
    return 0;
}