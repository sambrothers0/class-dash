#include "ui/screens/GameScreen.hpp"
#include "GameLogic.hpp"
#include "levels/Level.hpp"

#include "SDL2_gfxPrimitives.h"

// Helper functions for if a key is pressed
bool isMoveLeftPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_LEFT] || keysPressed[SDL_SCANCODE_A];
}

bool isMoveRightPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_RIGHT] || keysPressed[SDL_SCANCODE_D];
}

void GameScreen::drawLevel(std::shared_ptr<Level> level) {
    for (auto block : level->getBlocks()) {
        boxRGBA(renderer, block.getX() * 32 - scrollOffset, block.getY() * 32, (block.getX() + 1) * 32 - scrollOffset, (block.getY() + 1) * 32, 255, 255, 255, 255);
    }
}

void GameScreen::draw() {
    // Draw a box for the player
    Player& player = gameLogic.getPlayer();
    Vector2 playerPosition = player.getPosition();

    // Calculate the scroll offset
    scrollOffset = gameLogic.getScrollOffset();

    boxRGBA(renderer, playerPosition.getX() - 20 - scrollOffset, playerPosition.getY() - 20, playerPosition.getX() + 20 - scrollOffset, playerPosition.getY() + 20, 0, 255, 255, 255);
    
    boxRGBA(renderer, 0, 600, 1024, 768, 0, 255, 25, 255); //HARD CODED GAME DIMENSIONS AND GROUND HEIGHT FIX LATER

    // Render the level
    drawLevel(gameLogic.getLevel());

    // Draw the test text
    testText.draw();
}

ScreenType GameScreen::handleEvent(SDL_Event& event) {
    Player& player = gameLogic.getPlayer();
    MoveDirection direction = player.getCurrentDirection();

    const Uint8* keysPressed = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return ScreenType::PAUSE; // Switch to pause screen
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

    return ScreenType::KEEP;
}