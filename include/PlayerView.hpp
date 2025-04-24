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

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    TTF_Font* font = nullptr;

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

    // Handles extra SDL events that aren't specifically covered by SDL_Event, such as ensuring that a key is still held down
    void handleExtraEvents();

    // Switches to the title screen
    void switchToTitleScreen();

    // Switches to the how to play screen
    void switchToHowToPlayScreen();

    // Switches to the level select screen
    void switchToLevelSelectScreen();

    // Switches to the pause screen
    void switchToPauseScreen();

    // Switches to the game screen
    void switchToGameScreen();

    // Switches to the pause confirm quit screen
    void switchToPauseConfirmQuitScreen();
    
    // Switches to the level lose screen
    void switchToLevelLoseScreen();

    void switchToLevelWinScreen();

    // Pass Renderer
    SDL_Renderer* getRenderer() {
        return renderer;
    }


    ~PlayerView();
};

#endif