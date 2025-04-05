#ifndef _PLAYER_VIEW_H
#define _PLAYER_VIEW_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

#include "ui/screens/Screen.hpp"

#include <memory>

class Game;

class PlayerView {
    private:
    Game& game;

    SDL_Renderer* renderer;
    SDL_Window* window;
    TTF_Font* font;

    // Pointer to the current screen, it needs a pointer because Screen is an abstract class
    // This needs to be set in the constructor
    std::unique_ptr<Screen> screen;

    // Set up SDL
    void setupSDL();

    public:
    PlayerView(Game& _game) : game(_game) {}

    void init();

    void draw();

    // Handles an SDL event
    void handleEvent(SDL_Event& event);

    // Switches to the title screen
    void switchToTitleScreen();

    // Switches to the level select screen
    void switchToLevelSelectScreen();

    // Switches to the pause screen
    void switchToPauseScreen();

    // Switches to the game screen
    void switchToGameScreen();

    void switchToPauseConfirmQuitScreen();

    // Pass Renderer
    SDL_Renderer* getRenderer() {
        return renderer;
    }


    ~PlayerView();
};

#endif