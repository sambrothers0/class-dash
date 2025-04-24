#include "ui/screens/LevelLoseScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

void LevelLoseScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    title.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    if (cursorPosition == 0) {
        buttonColor = highlightedColor;
        restart.setText(">Restart<");
    } else {
        buttonColor = defaultColor;
        restart.setText("Restart");
    }
    drawButton(512 - 200, 260, 400, 75, buttonColor);
    restart.draw();

    if (cursorPosition == 1) {
        buttonColor = highlightedColor;
        quit.setText(">Quit<");
    } else {
        buttonColor = defaultColor;
        quit.setText("Quit");
    }
    drawButton(512 - 200, 360, 400, 75, buttonColor);
    quit.draw();
}

ScreenType LevelLoseScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SWITCH);
                cursorPosition = (cursorPosition - 1 + 2) % 2; // Wrap around
                break;
            case SDLK_DOWN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SWITCH);
                cursorPosition = (cursorPosition + 1) % 2; // Wrap around
                break;
            case SDLK_RETURN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                if (cursorPosition == 0) {
                    return ScreenType::GAME; // Resume the game
                } else if (cursorPosition == 1) {
                    return ScreenType::LEVEL_SELECT; // Quit to level select
                }
            case SDLK_ESCAPE:
                return ScreenType::LEVEL_SELECT;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}