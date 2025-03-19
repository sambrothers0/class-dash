#include "ui/screens/GameScreen.hpp"
#include "GameLogic.hpp"

#include "SDL2_gfxPrimitives.h"

// Helper functions for if a key is pressed
bool isMoveLeftPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_LEFT] || keysPressed[SDL_SCANCODE_A];
}

bool isMoveRightPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_RIGHT] || keysPressed[SDL_SCANCODE_D];
}

void GameScreen::draw() {
    // Draw a box for the player
    Player& player = gameLogic.getPlayer();
    Vector2 playerPosition = player.getPosition();

    boxRGBA(renderer, playerPosition.getX() - 20, playerPosition.getY() - 20, playerPosition.getX() + 20, playerPosition.getY() + 20, 0, 255, 255, 255);
    
    boxRGBA(renderer, 0, 600, 1024, 768, 0, 255, 25, 255); //HARD CODED GAME DIMENSIONS AND GROUND HEIGHT FIX LATER

}

unsigned int GameScreen::handleEvent(SDL_Event& event) {
    Player& player = gameLogic.getPlayer();
    MoveDirection direction = player.getCurrentDirection();

    const Uint8* keysPressed = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return 4; // Switch to pause screen
            case SDLK_LEFT:
            case SDLK_a:
                player.moveLeft();
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                player.moveRight();
                break;
            case SDLK_UP:
            case SDLK_w:
                player.jump();
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                if (direction == MoveDirection::LEFT && !isMoveLeftPressed(keysPressed)) {
                    player.stopMoving();
                }
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                if (direction == MoveDirection::RIGHT && !isMoveRightPressed(keysPressed)) {
                    player.stopMoving();
                }
                break;
                
        }
    }
    return 0;
}