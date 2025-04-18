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

Screen::~Screen() {}