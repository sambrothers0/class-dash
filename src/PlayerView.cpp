#include "PlayerView.hpp"

#include "Game.hpp"
#include "gameDimensions.hpp"
#include "sdlLogging.hpp"
#include "ui/screens/GameScreen.hpp"
#include "ui/screens/LevelSelectScreen.hpp"
#include "ui/screens/PauseConfirmQuitScreen.hpp"
#include "ui/screens/PauseScreen.hpp"
#include "ui/screens/TitleScreen.hpp"
#include "ui/screens/HowToPlayScreen.hpp"

void PlayerView::setupSDL() {
    // Create window
    window = SDL_CreateWindow("Class Dash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == NULL)
        sdlError("Could not create window!");

    if (TTF_Init() < 0)
        ttfError("Unable to initialize TTF!");

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        sdlError("Unable to initialize SDL_image!");
    }

    // Load font
    font = TTF_OpenFont("../assets/fonts/PressStart2P-Regular.ttf", 100);

    if (font == NULL)
        ttfError("Unable to open Arial font!");

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
        sdlError("Could not create renderer!");
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
    if (eventStatus == ScreenType::TITLE) {
        switchToTitleScreen();
    } else if (eventStatus == ScreenType::HOW_TO_PLAY) {
        switchToHowToPlayScreen();
    } else if (eventStatus == ScreenType::LEVEL_SELECT) {
        switchToLevelSelectScreen();
    } else if (eventStatus == ScreenType::GAME) {
        switchToGameScreen();
    } else if (eventStatus == ScreenType::PAUSE) {
        switchToPauseScreen();
    } else if (eventStatus == ScreenType::PAUSE_CONFIRM_QUIT) {
        switchToPauseConfirmQuitScreen();
    }
}

void PlayerView::switchToTitleScreen() {
    screen = std::make_unique<TitleScreen>(TitleScreen(renderer, font));
}

void PlayerView::switchToHowToPlayScreen() {
    screen = std::make_unique<HowToPlayScreen>(HowToPlayScreen(renderer, font));
}

void PlayerView::switchToLevelSelectScreen() {
    // Reset level if quitting out
    auto& gameLogic = game.getGameLogic();

    if (gameLogic.isLevelPaused()) {
        gameLogic.quitLevel();
    }

    screen = std::make_unique<LevelSelectScreen>(LevelSelectScreen(renderer, font, gameLogic.getLevelsCompleted()));
}

void PlayerView::switchToPauseScreen() {
    auto& gameLogic = game.getGameLogic();
    gameLogic.pause();
    screen = std::make_unique<PauseScreen>(PauseScreen(renderer, font));
}

void PlayerView::switchToGameScreen() {
    auto& gameLogic = game.getGameLogic();

    // Tell the game logic to update the level
    if (gameLogic.isNoLevelActive()) {
        game.getGameLogic().activate(renderer);
    } else {
        // If there is a level active, then resume the level
        gameLogic.resume();
    }

    screen = std::make_unique<GameScreen>(GameScreen(renderer, game.getGameLogic(), font));
}

void PlayerView::switchToPauseConfirmQuitScreen() {
    screen = std::make_unique<PauseConfirmQuitScreen>(PauseConfirmQuitScreen(renderer, font));
}

PlayerView::~PlayerView() {
    // SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();

    // SDL_DestroyRenderer(renderer); // (this line segfaults)
    // renderer = nullptr;
    SDL_DestroyWindow(window);
}