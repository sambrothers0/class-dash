#include "characters/Player.hpp"
#include "gameDimensions.hpp"
#include "physics/physicsConstants.hpp"
#include <iostream>
#include <cmath>
#include <vector>

#include <cmath>

const int GROUND_HEIGHT = 608; //This is just the current ground height based on how player position is called in GameLogic
const float JUMP_HEIGHT = 100.0f;

int Player::getCurrentAnimationOffset() const {
    return (animationTicks % 40) / 10;
}

void Player::move(double ms) {    
    // Basic character movement
    double seconds = ms / 1000;

    // Only apply vertical acceleration if the player is not on the ground
    if (!onGround) {
        velocity.setY(velocity.getY() + GRAVITY * seconds);

        // Once the jump has reached its maximum height, start falling
        if (isJumping && velocity.getY() > 0) {
            falling = true;
        }
    }

    position += velocity * seconds;

    // Deal with more advanced functionality
    if (currentDirection != MoveDirection::NONE) {
        animationTicks++;
    }

    handleCollisions();

    // Move the projectiles, while marking any which should be deleted
    std::vector<size_t> toDelete;

    for (size_t idx = 0; idx < projectiles.size(); idx++) {
        auto& proj = projectiles[idx];

        if (proj.isActive()) {
            proj.move(ms);
        } else {
            toDelete.push_back(idx);
        }
    }

    // Delete the corresponding indexes
    if (toDelete.size() > 0) {
        // This is needed to keep the indexes accurate
        int deleted = 0;

        for (auto idx : toDelete) {
            projectiles.erase(projectiles.begin() + idx - deleted);
            deleted++;
        }
    }
}

BoundingBox Player::getHitbox() const {
    // The hitbox is different if the player is flipped
    if (lastDirection == MoveDirection::RIGHT) {
        return hitbox;
    } else {
        auto oldOffset = hitbox.getOffset();

        return BoundingBox(
            Vector2(-12, oldOffset.getY()), // -12 is a magic number here, but it is the correct offset for flipping the player sprite
            hitbox.getSize()
        );
    }
}

// Callback for the projectile timer
Uint32 onProjectileTimer(Uint32 interval, void *param) {
    auto* player = reinterpret_cast<Player*>(param);

    player->setIfProjectileTimerActive(false);

    return 0; // Don't repeat
}

void Player::shoot() {
    if (isProjectileTimerActive) {
        return;
    }

    auto newProjectile = Projectile(position, currentDirection);

    if (currentDirection == MoveDirection::LEFT) {
        newProjectile.setStartingPosition(currentDirection);
        newProjectile.setVelocity(-300, 0);
    } else if (currentDirection == MoveDirection::RIGHT) {
        newProjectile.setStartingPosition(currentDirection);
        newProjectile.setVelocity(300, 0);
    } else if (lastDirection == MoveDirection::LEFT) {
        newProjectile.setStartingPosition(lastDirection);
        newProjectile.setVelocity(-300, 0);
    } else {
        newProjectile.setStartingPosition(MoveDirection::RIGHT);
        newProjectile.setVelocity(300, 0);
    }

    // Add to the list of projectiles if there aren't already too many
    if (projectiles.size() < MAX_PROJECTILES) {
        projectiles.push_back(newProjectile);
    }

    // Set up the projectile timer
    isProjectileTimerActive = true;
    projectileTimerId = SDL_AddTimer(PROJECTILE_DELAY, onProjectileTimer, this);
}

void Player::stopMoving() {
    velocity.setX(0);

    currentDirection = MoveDirection::NONE;
    animationTicks = 0;
    // velocity = Vector2(0, 0);
}

void Player::moveLeft() {
    velocity.setX(-250);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
    // velocity = Vector2(-250, 0);
}

void Player::moveRight() {
    velocity.setX(250);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
    // velocity = Vector2(250, 0);
}

void Player::jump() {
    if (velocity.getY() == 0) {
        std::cout << "jump" << std::endl;
        velocity.setY(-500);
        position -= Vector2(0, 1); // Update position to avoid an immediate collision with the ground
        bufferedJump = false;
        onGround= false;
        isJumping = true;
        falling = false;

        // Fall height isn't applicable
        fallHeight = -1000;
    } else {
        bufferedJump = true;
    }
}

Vector2 Player::getHitboxCenter() const {
    return position + hitbox.getOffset() + hitbox.getSize() / 2.0;
}

void Player::handleFloorCollisions() {
    // If the player is on the ground, confirm that they are still on the ground by checking for a collision
    // Otherwise, check if the player has collided with the ground. If they have, set them as on the ground and update their position + velocity. If they have a buffered jump, then jump.

    /**
     * if onGround {
     *   if player is not on the ground {
     *     set onGround to false
     *     set falling to true
     *   }
     * } else {
     *   if player is colliding with the ground {
     *     if falling and the collided tile is on the same y-level as the original falling location {
     *       continue
     *     } else if jumping and not falling {
     *       continue
     *     } else if bufferedJump {
     *       jump (should set isJumping to true)
     *     } else {
     *       set position to be on top of the block
     *       reset vertical velocity
     *       set onGround to true
     *     }
     *   }
     * }
     * 
     */

    auto hitbox = getHitbox() + position;

    auto level = gameLogic.getLevel();
    auto topY = hitbox.getTopY();
    auto bottomY = hitbox.getBottomY();
    auto leftX = hitbox.getLeftX();
    auto rightX = hitbox.getRightX();

    // std::cout << position << ", " << hitbox.getOffset() << std::endl;

     if (onGround) {
        bool isOnGround = false;

        for (auto x = leftX; x <= rightX; x += TILE_SIZE / 2) {
            if (level->getWorldCollisionObject(Vector2(floor(x / TILE_SIZE), floor(bottomY / TILE_SIZE)))) {
                isOnGround = true;
                break;
            }
        }

        if (!isOnGround) {
            // Start falling
            onGround = false;
            falling = true;
            fallHeight = bottomY;
        }
     } else {
        for (auto x = leftX; x <= rightX; x += TILE_SIZE / 2) {
            auto tileX = floor(x / TILE_SIZE);
            auto tileY = floor(bottomY / TILE_SIZE);
            auto worldTile = level->getWorldCollisionObject(Vector2(tileX, tileY));

            // This line is the key
            if (worldTile) {
                // If partOfWall is true, then we are against a wall and should not be able to jump or land.
                auto partOfWall = level->getWorldCollisionObject(Vector2(tileX, tileY - 1));

                auto tilePos = worldTile->bounds;

                // Falling off the same height
                if (falling && tilePos.y == fallHeight) {
                    continue;
                } else if (isJumping && !falling) {
                    continue;
                } else if (bufferedJump) {
                    jump();
                }
                // std::cout << tilePos.y << ", " << bottomY << std::endl;

                if (!partOfWall) {
                    std::cout << "Hit ground" << std::endl;
                    position.setY(tilePos.y - PLAYER_HEIGHT / 2);
                    velocity.setY(0);
                    isJumping = false;
                    onGround = true;
                    falling = false;
                    break;
                }
            }
        }
     }
}

void Player::handleCeilingCollisions() {
    auto hitbox = getHitbox() + position;
    auto level = gameLogic.getLevel();
    
    auto hitboxWidth = hitbox.getSize().getX();
    auto hitboxHeight = hitbox.getSize().getY();

    auto topY = hitbox.getTopY();
    auto bottomY = hitbox.getBottomY();
    auto leftX = hitbox.getLeftX();
    auto rightX = hitbox.getRightX();
    int unused;

    // The idea is to factor in if the player is moving in a direction
    for (auto x = (currentDirection == MoveDirection::LEFT ? leftX + 4 : leftX); x <= (currentDirection == MoveDirection::RIGHT ? rightX - 8 : rightX); x += TILE_SIZE / 2) {
        auto collideWorld = level->getWorldCollisionObject(Vector2(floor(x / TILE_SIZE), floor(topY / TILE_SIZE)));

        if (collideWorld) {
            std::cout << "ceiling collision" << std::endl;
            // position.setX(collideWorld->bounds.x - hitboxWidth);
            position.setY(collideWorld->bounds.y + collideWorld->bounds.h + PLAYER_HEIGHT / 2 + 1);
            velocity.setY(0.1);
            falling = true;
            break;

        }
    }
}

void Player::handleRightCollisions() {
    auto hitbox = getHitbox() + position;
    auto level = gameLogic.getLevel();
    
    auto hitboxWidth = hitbox.getSize().getX();
    auto hitboxHeight = hitbox.getSize().getY();

    auto topY = hitbox.getTopY();
    auto bottomY = hitbox.getBottomY();
    auto leftX = hitbox.getLeftX();
    auto rightX = hitbox.getRightX();

    for (auto y = topY; y <= bottomY - 1; y += TILE_SIZE / 2) {
        auto collideWorld = level -> getWorldCollisionObject(Vector2(floor(rightX / TILE_SIZE), floor(y / TILE_SIZE)));

        if (collideWorld) {
            auto bounds = collideWorld->bounds;

            // The idea is to not have a collision because the block is too low/high
            if (bounds.y >= bottomY || (bounds.y + bounds.h <= topY)) {
                continue;
            }

            std::cout<<"Right Collision Detected"<<std::endl;
            // std::cout<<"X position"<< position.getX()<<" tile X; "<< collideWorld->bounds.x<<"player width" <<hitboxWidth<<" rightX *32 "<<rightX*TILE_SIZE<<std::endl;/
            // position.setX(collideWorld->bounds.x - hitboxWidth);
            position.setX(collideWorld->bounds.x - PLAYER_WIDTH / 2 - 1);
            velocity.setX(0);
            break;

        }
    }
}

void Player::handleLeftCollisions() {
    auto hitbox = getHitbox() + position;
    auto level = gameLogic.getLevel();
    
    auto hitboxWidth = hitbox.getSize().getX();
    auto hitboxHeight = hitbox.getSize().getY();

    auto topY = hitbox.getTopY();
    auto bottomY = hitbox.getBottomY();
    auto leftX = hitbox.getLeftX();
    auto rightX = hitbox.getRightX();

    for (auto y = topY; y <= bottomY-1; y += TILE_SIZE / 2) {
        auto collideWorld = level -> getWorldCollisionObject(Vector2(floor(leftX / TILE_SIZE), floor(y / TILE_SIZE)));

        if (collideWorld) {
            auto bounds = collideWorld->bounds;

            // The idea is to not have a collision because the block is too low/high
            if (bounds.y >= bottomY || (bounds.y + bounds.h <= topY)) {
                continue;
            }

            // std::cout<<"Left Collision Detected"<<std::endl;
            // std::cout<<"X position"<< position.getX()<<" tile X; "<< collideWorld->bounds.x+collideWorld->bounds.h<<"player width" <<hitboxWidth<<" leftX*32 "<<leftX*TILE_SIZE<<std::endl;
            position.setX(collideWorld->bounds.x + collideWorld->bounds.w + PLAYER_WIDTH / 2 + 1);
            // position.setX(collideWorld->bounds.x+collideWorld->bounds.w+(PLAYER_WIDTH/2)+1);
            velocity.setX(0);
        }
    }
}

void Player::handleCollisions() {
    /**
     * if player is hitting an obstacle to the right and is moving right, push them back
     * if player is hitting an obstacle to the left and is moving left, push them back
     * check bottom tiles
     * check top tiles
     * 
     * To fix one issue, if the player is falling off of a structure, don't check vertically unless the new position is lower
     * If the player is jumping, only check vertically once they reach the peak of their jump
     */

     handleFloorCollisions();

     if (velocity.getY() < 0)
        handleCeilingCollisions();

     if (velocity.getX() > 0) {
        handleRightCollisions();
     } else if (velocity.getX() < 0) {
        handleLeftCollisions();
     }
}
