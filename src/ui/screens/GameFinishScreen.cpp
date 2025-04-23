#include "ui/screens/GameFinishScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

void GameFinishScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    title.draw();
    subtitle1.draw();
    subtitle2.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    buttonColor = highlightedColor;
    quit.setText(">Quit<");

    drawButton(512 - 200, 360, 400, 75, buttonColor);
    quit.draw();
}

void GameFinishScreen::drawBackground(SDL_Renderer* renderer, SDL_Texture* texture) {
    // only load the image if it hasn't been loaded yet
    if (!background) {
        SDL_Surface* surface = IMG_Load("../assets/visual/title-screen-bg.png");
        if (!surface) {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        }
    
        background = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    
        if (!background) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }
    }
    // Render to the screen
    SDL_RenderCopy(renderer, texture, NULL, NULL);

}

ScreenType GameFinishScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::LEVEL_SELECT; // Quit to title screen
            case SDLK_ESCAPE:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::LEVEL_SELECT; // Quit to level select
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}