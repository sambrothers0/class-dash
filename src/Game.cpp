#include "Game.hpp"

void Game::run() {
    /*** Main Loop ***/
    SDL_Event e;

    while (isRunning) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) 
                isRunning = false;

            // User presses a key
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) 
                    isRunning = false;
            }
        }
    }
}