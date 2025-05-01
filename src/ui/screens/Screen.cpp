#include "ui/screens/Screen.hpp"

void Screen::drawButton(int x, int y, int width, int height, SDL_Color color) {
    // Set the color for the button
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Half the height determines the rounding
    int radius = height / 2; 

    // Draw center rectangle
    SDL_Rect rect = {x + radius, y, width - height, height}; 
    SDL_RenderFillRect(renderer, &rect);

    // Draw two circles at each end
    drawCircle(x + radius, y + radius, radius);
    drawCircle(x + width - radius, y + radius, radius);
}

void Screen::drawCircle(int cx, int cy, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal offset
            int dy = radius - h; // Vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void Screen::drawBackground(std::string imagePath) {
    // only load the image if it hasn't been loaded yet
    if (!background) {
        SDL_Surface* surface = IMG_Load(imagePath.c_str());
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
    SDL_RenderCopy(renderer, background, NULL, NULL);

}

Screen::~Screen() {}