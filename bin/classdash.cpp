#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Game.hpp"
#include "GameConstants.hpp"


void sdl_error(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    exit(0);
}

int main(int argc, char** argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
        sdl_error("Failed to initialize SDL!");

    // Create window
    SDL_Window* window = SDL_CreateWindow("Class Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
        sdl_error("Could not create window!");

    // Init Bitmap loading
    if( IMG_Init( IMG_INIT_PNG ) < 0 ) sdl_error("SDL could not initialize bitmap loaders!");

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        sdl_error("Could not create renderer!");

    // convert to texture
    SDL_Texture* texture = IMG_LoadTexture(renderer, "../assets/visual/spritesheet.png");

    if (texture == NULL)
        sdl_error("Could not create texture from surface!");

    // Set up game object
    Game game(renderer);

    game.run();

    // Cleanup
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}