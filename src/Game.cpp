#include "Game.hpp"

void Game::run() {
    /*** Main Loop ***/
    SDL_Event e;

    // Set up objects
    playerView.init();

    // Create a test level
    Level level(Vector2(4096, 768));
    level.setBlocks({
        Vector2(0, 4),
        Vector2(1, 4),
        Vector2(2, 6),
        Vector2(2, 5),
        Vector2(3, 7),
        Vector2(3, 4),
        Vector2(20, 3),
        Vector2(40, 7),
        Vector2(60, 9),
        Vector2(65, 1)
    });

    gameLogic.setLevel(std::make_shared<Level>(level));

    bool isRunning = true;

    Uint64 ticks = SDL_GetTicks64();

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

            // Player view handles extra events
            playerView.handleEvent(e);
        }

        // Draw the player view
        playerView.draw();

        // Get the difference in ticks (ms)
        Uint64 ticks2 = SDL_GetTicks64();
        Uint64 difference = ticks2 - ticks;
        ticks = ticks2;

        gameLogic.runTick(difference);

        // Delay to avoid lag
        SDL_Delay(1);
    }
}