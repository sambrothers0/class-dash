#include "ui/screens/PauseConfirmQuitScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void PauseConfirmQuitScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    confirm.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    if (cursorPosition == 0) {
        buttonColor = highlightedColor;
        yes.setText(">Yes<");
    } else {
        buttonColor = defaultColor;
        yes.setText("Yes");
    }
    drawButton(512 - 200, 260, 400, 75, buttonColor);
    yes.draw();

    if (cursorPosition == 1) {
        buttonColor = highlightedColor;
        no.setText(">No<");
    } else {
        buttonColor = defaultColor;
        no.setText("No");
    }
    drawButton(512 - 200, 360, 400, 75, buttonColor);
    no.draw();
}

ScreenType PauseConfirmQuitScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                cursorPosition = (cursorPosition - 1 + 2) % 2; // Wrap around
                break;
            case SDLK_DOWN:
                cursorPosition = (cursorPosition + 1) % 2; // Wrap around
                break;
            case SDLK_RETURN:
                if (cursorPosition == 0) {
                    return ScreenType::LEVEL_SELECT; // Resume the game
                } else if (cursorPosition == 1) {
                    return ScreenType::GAME; // Quit to level select
                }
            case SDLK_ESCAPE:
                return ScreenType::LEVEL_SELECT;
            default:
                return ScreenType::KEEP;
        }
    }
    

    return ScreenType::KEEP;
}