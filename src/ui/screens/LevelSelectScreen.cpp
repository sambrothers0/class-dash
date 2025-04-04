#include "ui/screens/LevelSelectScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void LevelSelectScreen::draw() {
    // Draw the level select screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    selectText.draw();

    drawButton(renderer, 512 - 200, 160, 400, 75, {147, 115, 64, 255});
    monday.draw();

    drawButton(renderer, 512 - 200, 260, 400, 75, {147, 115, 64, 255});
    tuesday.draw();

    drawButton(renderer, 512 - 200, 360, 400, 75, {147, 115, 64, 255});
    wednesday.draw();

    drawButton(renderer, 512 - 200, 460, 400, 75, {147, 115, 64, 255});
    thursday.draw();

    drawButton(renderer, 512 - 200, 560, 400, 75, {147, 115, 64, 255});
    friday.draw();

    drawButton(renderer, 512 - 250, 665, 500, 60, {147, 115, 64, 255});
    back.draw();
}

ScreenType LevelSelectScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                return ScreenType::GAME; // Switch to game screen
            case SDLK_RETURN:
                return ScreenType::GAME; // Switch to game screen
            case SDLK_ESCAPE:
                return ScreenType::TITLE; // Switch to title screen
            default:
                return ScreenType::KEEP;
        }
    }
    return ScreenType::KEEP;
}