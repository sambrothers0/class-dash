#include "ui/screens/TitleScreen.hpp"

#include <SDL_image.h>
#include <iostream>

void TitleScreen::draw() {
    // Draw the background
    drawBackground(backgroundPath);

    // Draw the title text
    title.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons


    // Draw the first button (Start Button)
    if (cursorPosition == 0) {
        buttonColor = highlightedColor;
        start.setText(">Start<");
    } else {
        buttonColor = defaultColor;
        start.setText("Start");

    }
    drawButton(512 - 170, 384 + 150, 350, 100, buttonColor);
    start.draw();

    // Draw the second button (How to Play Button)
    if (cursorPosition == 1) {
        buttonColor = highlightedColor;
        howToPlay.setText(">How To Play<");
    } else {
        buttonColor = defaultColor;
        howToPlay.setText("How To Play");
    }
    drawButton(512 - 220, 384 + 275, 450, 75, buttonColor);
    howToPlay.draw();

}

ScreenType TitleScreen::handleEvent(SDL_Event& event) {
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
                    return ScreenType::LEVEL_SELECT; // Switch to level select screen
                } else if (cursorPosition == 1) {
                    return ScreenType::HOW_TO_PLAY; // Switch to how to play screen
                }
                break;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}

TitleScreen::~TitleScreen() {
    // Clean up the texture
    SDL_DestroyTexture(background); 
}