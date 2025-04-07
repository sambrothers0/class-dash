#include "ui/screens/LevelSelectScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void LevelSelectScreen::draw() {
    // Draw the level select screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    selectText.draw();
    // may be a better way of doing this cursor logic, but this works for now
    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    if (cursorPosition == 0) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 200, 160, 400, 75, buttonColor);
    monday.draw();

    if (cursorPosition == 1) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 200, 260, 400, 75, buttonColor);
    tuesday.draw();

    if (cursorPosition == 2) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 200, 360, 400, 75, buttonColor);
    wednesday.draw();

    if (cursorPosition == 3) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 200, 460, 400, 75, buttonColor);
    thursday.draw();

    if (cursorPosition == 4) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 200, 560, 400, 75, buttonColor);
    friday.draw();

    if (cursorPosition == 5) {
        buttonColor = highlightedColor;
    } else {
        buttonColor = defaultColor;
    }
    drawButton(renderer, 512 - 150, 665, 300, 60, buttonColor);
    back.draw();
}

ScreenType LevelSelectScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                cursorPosition = (cursorPosition - 1 + 6) % 6; // Wrap around
                break;
            case SDLK_DOWN:
                cursorPosition = (cursorPosition + 1) % 6; // Wrap around
                break;
            case SDLK_RETURN:
                if (cursorPosition != 5) {
                    return ScreenType::GAME; // this may need additional work to select correct level later
                } else {
                    return ScreenType::TITLE; // Switch to title screen
                }
            case SDLK_ESCAPE:
                return ScreenType::TITLE; // Switch to title screen
            default:
                return ScreenType::KEEP;
        }
    }
    return ScreenType::KEEP;
}