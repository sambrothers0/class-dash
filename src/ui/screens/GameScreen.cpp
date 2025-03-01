#include "ui/screens/GameScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void GameScreen::draw() {
    // Draw a box for the player
    Player& player = gameLogic.getPlayer();
    Vector2 playerPosition = player.getPosition();

    boxRGBA(renderer, playerPosition.getX() - 20, playerPosition.getY() - 20, playerPosition.getX() + 20, playerPosition.getY() + 20, 0, 255, 255, 255);
}

void GameScreen::handleEvent(SDL_Event& event) {
    Player& player = gameLogic.getPlayer();

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                player.moveLeft();
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                player.moveRight();
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
            case SDLK_RIGHT:
            case SDLK_d:
                player.stopMoving();
                break;
        }
    }
}