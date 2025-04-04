#include "ui/screens/PauseConfirmQuitScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void PauseConfirmQuitScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    confirmText.draw();
}

ScreenType PauseConfirmQuitScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                return ScreenType::LEVEL_SELECT;
            case SDLK_ESCAPE:
                return ScreenType::GAME;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}