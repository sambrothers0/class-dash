#include "Game.hpp"

#include <algorithm>

#include <iostream>

const int FPS = 60;
const int FRAMETIME = 1000 / FPS;

void Game::run() {
    /*** Main Loop ***/
    SDL_Event e;

    // Set up objects
    gameLogic.init();
    playerView.init();

    // Load the level
    SDL_Renderer* renderer = playerView.getRenderer();
    std::shared_ptr<Level> level = std::make_shared<Level>(Vector2(2240, 768), renderer);
    if (!level->loadFromTMX("../assets/visual/ColliderTest.tmx", renderer)) {
        std::cerr << "Failed to load level!" << std::endl;
        return;
    }

    gameLogic.setLevel(level);

    bool isRunning = true;

    Uint64 ticks = SDL_GetTicks64();

    while (isRunning) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }

            // User presses a key
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) {
                    isRunning = false;
                }
            }

            // Player view handles extra events
            playerView.handleEvent(e);
        }

        // Player view handles extra events
        playerView.handleExtraEvents();

        // Draw the player view
        playerView.draw();

        // Get the difference in ticks (ms)
        Uint64 ticks2 = SDL_GetTicks64();
        Uint64 difference = ticks2 - ticks;
        ticks = ticks2;

        gameLogic.runTick(difference);
        
        // Set to 60 fps
        if (difference < FRAMETIME) {
            SDL_Delay(std::max((Uint64) 1, FRAMETIME - difference));
        }
    }
}