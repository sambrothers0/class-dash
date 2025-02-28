#include <SDL.h>

#include <iostream>
#include <string>

void sdl_error(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    exit(0);
}

int main(int argc, char** argv) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
        sdl_error("Failed to initialize SDL!");

    // Create window
    SDL_Window* window = SDL_CreateWindow("Class Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

    if (window == NULL)
        sdl_error("Could not create window!");

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        sdl_error("Could not create renderer!");


    /*** Main Loop ***/
    bool running = true;
    SDL_Event e;

    while (running) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) 
                running = false;

            // User presses a key
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) 
                    running = false;
            }
        }
    }

    // SDL_Delay(1000);

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}