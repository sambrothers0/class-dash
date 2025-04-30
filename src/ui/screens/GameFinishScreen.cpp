#include "ui/screens/GameFinishScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

void GameFinishScreen::draw() {
    // Draw the title screen
    // boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder
    drawBackground(backgroundPath);

    title.draw();
    subtitle1.draw();
    subtitle2.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    buttonColor = highlightedColor;
    quit.setText(">Quit<");

    drawButton(512 - 200, 660, 400, 75, buttonColor);
    quit.draw();
}

ScreenType GameFinishScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::TITLE; // Quit to title screen
            case SDLK_ESCAPE:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::TITLE; // Quit to title screen
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}