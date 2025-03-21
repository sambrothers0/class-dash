#include "ui/screens/TitleScreen.hpp"

#include "SDL2_gfxPrimitives.h"
#include <iostream>

void TitleScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    playText.draw();
}

ScreenType TitleScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                return ScreenType::LEVEL_SELECT;
            case SDLK_RETURN:
                return ScreenType::LEVEL_SELECT;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}