#include <SDL.h>

#include "Game.hpp"
#include "sdlLogging.hpp"
#include <ctime>

int main(int argc, char** argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
        sdlError("Failed to initialize SDL!");

    std::srand(std::time({}));

    // Set up game object
    Game game;

    game.run();

    // Cleanup
    SDL_Quit();

    return 0;
}