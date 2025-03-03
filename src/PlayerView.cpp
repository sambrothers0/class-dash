#include "PlayerView.hpp"

#include "ui/screens/GameScreen.hpp"
#include "ui/screens/TitleScreen.hpp"

PlayerView::PlayerView(SDL_Renderer *_renderer, GameLogic& _gameLogic) : renderer(_renderer), gameLogic(_gameLogic) {
    switchToGameScreen();
}

void PlayerView::draw() {
    // Clear the renderer first
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    screen->draw();

    SDL_RenderPresent(renderer);
}

void PlayerView::handleEvent(SDL_Event& event) {
    screen->handleEvent(event);
}

void PlayerView::switchToTitleScreen() {
    screen = std::make_unique<TitleScreen>(TitleScreen(renderer, gameLogic));
}

void PlayerView::switchToGameScreen() {
    screen = std::make_unique<GameScreen>(GameScreen(renderer, gameLogic));
}