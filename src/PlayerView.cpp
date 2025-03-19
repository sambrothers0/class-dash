#include "PlayerView.hpp"

#include "Game.hpp"
#include "gameDimensions.hpp"
#include "sdlLogging.hpp"
#include "ui/screens/GameScreen.hpp"
#include "ui/screens/LevelSelectScreen.hpp"
#include "ui/screens/PauseScreen.hpp"
#include "ui/screens/TitleScreen.hpp"

void PlayerView::setupSDL() {
    // Create window
    window = SDL_CreateWindow("Class Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
        sdlError("Could not create window!");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        sdlError("Could not create renderer!");

    // // convert to texture (commented out until we optimize the size)
    // SDL_Texture* texture = IMG_LoadTexture(renderer, "../assets/visual/spritesheet.png");

    // if (texture == NULL)
    //     sdl_error("Could not create texture from surface!");
}

void PlayerView::init() {
    setupSDL();
    switchToTitleScreen();
}

void PlayerView::draw() {
    // Clear the renderer first
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    screen->draw();

    SDL_RenderPresent(renderer);
}

void PlayerView::handleEvent(SDL_Event& event) {
    int eventStatus = screen->handleEvent(event);
    if (eventStatus == 1) {
        switchToTitleScreen();
    } else if (eventStatus == 2) {
        switchToLevelSelectScreen();
    } else if (eventStatus == 3) {
        switchToGameScreen();
    } else if (eventStatus == 4) {
        switchToPauseScreen();
    }
}

void PlayerView::switchToTitleScreen() {
    screen = std::make_unique<TitleScreen>(TitleScreen(renderer));
}

void PlayerView::switchToLevelSelectScreen() {
    screen = std::make_unique<LevelSelectScreen>(LevelSelectScreen(renderer));
}

void PlayerView::switchToPauseScreen() {
    screen = std::make_unique<PauseScreen>(PauseScreen(renderer));
}

void PlayerView::switchToGameScreen() {
    screen = std::make_unique<GameScreen>(GameScreen(renderer, game.getGameLogic()));
}

PlayerView::~PlayerView() {
    // SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}