#include "ui/screens/TitleScreen.hpp"

#include <SDL_image.h>
#include <iostream>

void TitleScreen::draw() {
    // Draw the background
    drawBackground(renderer, background);

    // Draw the title text
    titleText.draw();

    // Draw the first button (Start Button)
    drawButton(renderer, 512 - 170, 384 + 150, 350, 100, {147, 115, 64, 255});
    startText.draw();

    // Draw the second button (How to Play Button)
    drawButton(renderer, 512 - 220, 384 + 275, 450, 75, {147, 115, 64, 255});
    howToPlayText.draw();

}

void TitleScreen::drawBackground(SDL_Renderer* renderer, SDL_Texture* texture) {
    if (!background) {
        // only load the image if it hasn't been loaded yet
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

ScreenType TitleScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                return ScreenType::LEVEL_SELECT;
            case SDLK_RETURN:
                return ScreenType::LEVEL_SELECT;
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