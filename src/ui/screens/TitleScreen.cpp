#include "ui/screens/TitleScreen.hpp"

#include "SDL2_gfxPrimitives.h"
#include <iostream>

void TitleScreen::draw() {
    // Draw the background
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); // background white

    // Draw the title text
    titleText.draw();

    // Draw the first button (Start Button)
    drawButton(renderer, 512 - 170, 384 + 65, 350, 100, {147, 115, 64, 255});
    startText.draw();

    // Draw the second button (How to Play Button)
    drawButton(renderer, 512 - 220, 384 + 175, 450, 75, {147, 115, 64, 255});
    howToPlayText.draw();
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