#include "ui/screens/GameScreen.hpp"
#include "GameLogic.hpp"
#include "gameDimensions.hpp"
#include "levels/Level.hpp"
#include "sprites/PlayerTexture.hpp"
#include "sprites/EnemyTexture.hpp"

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
        for (const auto& blocks : layer->getBlocks()) {
            auto block = std::get<0>(blocks);
            // auto block = blocks[0];
            auto flip = std::get<1>(blocks);
            uint32_t tileID = layer->getID(block);
            auto t = layer->hasFlipFlag(block);
            if(t){std::cout<<"got tile "<<tileID<<"flip flag? "<<t<<std::endl;}
            auto opacity = layer->getOpacity();


            // Quit out if hitboxes are not being shown and the given tile is a hitbox tile
            if (!showHitboxes && level->isHitboxGID(tileID)) {
                continue;
            }

            std::shared_ptr<Spritesheet> spritesheet = level->getSpritesheetForGID(tileID);

            if (!spritesheet) {
                std::cerr << "No spritesheet found for tile ID: " << tileID << std::endl;
                continue;
            }

            auto drawOffset = TILE_SIZE / 2;

            Vector2 blockPosition(block.getX() * TILE_SIZE - scrollOffset + drawOffset, block.getY() * TILE_SIZE + drawOffset);
            int spriteIndex = tileID - spritesheet->getFirstGID();

            spritesheet->draw(spriteIndex, blockPosition, flip, opacity);
        }
    }
}

void GameScreen::drawCollisionHitbox(const Vector2& position, const BoundingBox& hitbox) const {
    boxRGBA(renderer, position.getX() - scrollOffset + hitbox.getLeftX(), position.getY() + hitbox.getTopY(), position.getX() - scrollOffset + hitbox.getRightX(), position.getY() + hitbox.getBottomY(), 0, 255, 0, 100);
}

void GameScreen::draw() {
    if (!gameLogic.isLevelActive())
        return;

    // Draw a box for the player
    auto player = gameLogic.getPlayer();
    Vector2 playerPosition = player->getPosition();

    // Get the enemy and their position
    auto enemy = gameLogic.getEnemy();
    Vector2 enemyPosition = enemy->getPosition();

    // Calculate the scroll offset
    scrollOffset = gameLogic.getScrollOffset();

    // Determine which texture index to use
    PlayerTexture playerTexture = PlayerTexture::WALK1;
    auto level = gameLogic.getLevel();

    drawLevel(level);

    playerSprite.draw(PlayerTexture::WALK1 + player->getCurrentAnimationOffset(), playerPosition - Vector2(scrollOffset, 0), player->getLastDirection() == MoveDirection::LEFT, 1.0);

    enemySprite.draw(EnemyTexture::ENEMY1WALK1 + enemy->getCurrentAnimationOffset(), enemyPosition - Vector2(scrollOffset, 0), enemy->getLastDirection() == MoveDirection::RIGHT, 1.0);

    // Draw the player hitbox
    if (showHitboxes)
        drawCollisionHitbox(playerPosition, player->getHitbox());

    // Display the projectiles that have been shot
    for (auto proj : player->getProjectiles()) {
        Vector2 projectilePosition = proj.getPosition();
        //boxRGBA(renderer, projectilePosition.getX() - 10 - scrollOffset, projectilePosition.getY() - 10, projectilePosition.getX() + 10 - scrollOffset, projectilePosition.getY() + 10, 0, 255, 255, 255);
        if (proj.getVelocity().getX() < 0) {
            playerProjectileSprite.draw(3, projectilePosition - Vector2(scrollOffset, 0), false, 1.0);
        } 
        else {
            playerProjectileSprite.draw(3, projectilePosition - Vector2(scrollOffset, 0), true, 1.0);
        }      
    }
    
    // Display the Time on the screen
    timeText.setText(gameLogic.getTimer()->getTime());
    timeText.draw();
}

ScreenType GameScreen::handleEvent(SDL_Event& event) {
    if (!gameLogic.isLevelActive())
        return ScreenType::KEEP;

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

ScreenType GameScreen::handleExtraEvents() {
    // lose checking needs to happen outside handleEvent because 
    // we need to lose the level even if the player is not pressing any keys
    if (gameLogic.getTimer()->isTimeUp()) {
        return ScreenType::LEVEL_LOSE; // Switch to level lose screen
    }

    // Jump buffering handle needs to happen outside of HandleEvent because that can't tell if a key is still held down
    const Uint8* keysPressed = SDL_GetKeyboardState(NULL);
    auto player = gameLogic.getPlayer();

    if (isJumpPressed(keysPressed)) {
        player->jump();
    }

    if (isMoveLeftPressed(keysPressed)) {
        player->moveLeft();
    }

    if (isMoveRightPressed(keysPressed)) {
        player->moveRight();
    }
    
    return ScreenType::KEEP;
}