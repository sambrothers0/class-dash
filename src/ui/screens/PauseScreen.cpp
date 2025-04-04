#include "ui/screens/PauseScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

void PauseScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    pause.draw();

    drawButton(renderer, 512 - 350, 260, 700, 75, {147, 115, 64, 255});
    resume.draw();

    drawButton(renderer, 512 - 350, 360, 700, 75, {147, 115, 64, 255});
    quit.draw();
}

ScreenType PauseScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                return ScreenType::GAME;
            case SDLK_ESCAPE:
                return ScreenType::PAUSE_CONFIRM_QUIT;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}