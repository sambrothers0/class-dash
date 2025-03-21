#include "ui/screens/LevelSelectScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void LevelSelectScreen::draw() {
    // Draw the level select screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder
    
    selectText.draw();
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