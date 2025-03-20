#include "ui/screens/LevelSelectScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void LevelSelectScreen::draw() {
    // Draw the level select screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 0, 0, 255); //placeholder
    
}

unsigned int LevelSelectScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                return 3; // Switch to game screen
            case SDLK_RETURN:
                return 3; // Switch to game screen
            case SDLK_ESCAPE:
                return 1; // Switch to title screen
            default:
                return 0;
        }
    }
    return 0;
}