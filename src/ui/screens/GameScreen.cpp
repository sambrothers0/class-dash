#include "ui/screens/GameScreen.hpp"
#include "GameLogic.hpp"
#include "levels/Level.hpp"
#include "sprites/PlayerTexture.hpp"

#include "SDL2_gfxPrimitives.h"

#include <iostream>

// Helper functions for if a key is pressed
bool isMoveLeftPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_LEFT] || keysPressed[SDL_SCANCODE_A];
}

bool isMoveRightPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_RIGHT] || keysPressed[SDL_SCANCODE_D];
}

bool isJumpPressed(const Uint8* keysPressed) {
    return keysPressed[SDL_SCANCODE_UP] || keysPressed[SDL_SCANCODE_W];
}




void GameScreen::drawLevel(std::shared_ptr<Level> level) {
    for (const auto& layer : level->getLayers()) {
        for (const auto& block : layer->getBlocks()) {
            uint32_t tileID = layer->getID(block);

            // Quit out if hitboxes are not being shown and the given tile is a hitbox tile
            if (!showHitboxes && level->isHitboxGID(tileID)) {
                continue;
            }
            
            std::shared_ptr<Spritesheet> spritesheet = level->getSpritesheetForGID(tileID);
            
            if (!spritesheet) {
                std::cerr << "No spritesheet found for tile ID: " << tileID << std::endl;
                continue; 
            }

            auto drawOffset = 16;
        
            Vector2 blockPosition(block.getX() * 32 - scrollOffset + drawOffset, block.getY() * 32 + drawOffset);
            int spriteIndex = tileID - spritesheet->getFirstGID(); 
        
            spritesheet->draw(spriteIndex, blockPosition);
        }
    }
}

void GameScreen::drawCollisionHitbox(const Vector2& position, const BoundingBox& hitbox) const {
    boxRGBA(renderer, position.getX() - scrollOffset + hitbox.getLeftX(), position.getY() + hitbox.getTopY(), position.getX() - scrollOffset + hitbox.getRightX(), position.getY() + hitbox.getBottomY(), 0, 255, 0, 100);
}

void GameScreen::draw() {
    // Draw a box for the player
    auto player = gameLogic.getPlayer();
    Vector2 playerPosition = player->getPosition();

    // Calculate the scroll offset
    scrollOffset = gameLogic.getScrollOffset();

    // Determine which texture index to use
    PlayerTexture playerTexture = PlayerTexture::WALK1;
    auto level = gameLogic.getLevel();

    drawLevel(level);

    playerSprite.draw(PlayerTexture::WALK1 + player->getCurrentAnimationOffset(), playerPosition - Vector2(scrollOffset, 0), player->getLastDirection() == MoveDirection::LEFT);

    // Draw the player hitbox
    if (showHitboxes)
        drawCollisionHitbox(playerPosition, player->getHitbox());

    // Display the projectiles that have been shot
    for (auto proj : player->getProjectiles()) {
        Vector2 projectilePosition = proj.getPosition();
        boxRGBA(renderer, projectilePosition.getX() - 10 - scrollOffset, projectilePosition.getY() - 10, projectilePosition.getX() + 10 - scrollOffset, projectilePosition.getY() + 10, 0, 255, 255, 255);
    }
}

ScreenType GameScreen::handleEvent(SDL_Event& event) {
    auto player = gameLogic.getPlayer();
    MoveDirection direction = player->getCurrentDirection();

    const Uint8* keysPressed = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                return ScreenType::PAUSE; // Switch to pause screen
            case SDLK_LEFT:
            case SDLK_a:
                player->moveLeft();
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                player->moveRight();
                break;
            case SDLK_UP:
            case SDLK_w:
                std::cout << "jump pressed" << std::endl;
                player->jump();
                break;
            case SDLK_SPACE:
                player->shoot();
                break;
            case SDLK_h:
                // Toggle should only happen if h is not active
                if (!hitboxKeyActive) {
                    showHitboxes = !showHitboxes;
                    hitboxKeyActive = true;
                }
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_a:
                if (direction == MoveDirection::LEFT && !isMoveLeftPressed(keysPressed)) {
                    player->stopMoving();
                }
                break;

            case SDLK_RIGHT:
            case SDLK_d:
                if (direction == MoveDirection::RIGHT && !isMoveRightPressed(keysPressed)) {
                    player->stopMoving();
                }
                break;
            
            case SDLK_h:
                hitboxKeyActive = false;
                break;

            case SDLK_UP:
            case SDLK_w:
                // Disable jump buffer
                if (!isJumpPressed(keysPressed)) {
                    player->setBufferedJump(false);
                }
                break;
        }
    }

    return ScreenType::KEEP;
}