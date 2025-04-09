#include "characters/Player.hpp"
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
    Character::move(ms);

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
        velocity.setY(-500);
        position -= Vector2(0, 1); // Update position to avoid an immediate collision with the ground
        bufferedJump = false;
        onGround= false;
    } else {
        bufferedJump = true;
    }
}

Vector2 Player::getHitboxCenter() const {
    return position + hitbox.getOffset() + hitbox.getSize() / 2.0;
}



void Player::handleCollisions() {
    std::cout<<"ground?: "<<onGround<<std::endl;
    std::cout<<"POSITION: "<<position.getX()<<" "<<position.getY()<<"\n\n"<<std::endl;
    if (position.getY() >= 800 - PLAYER_HEIGHT / 2) { //THIS WILL NEED TO BE BASED ON COLLISIONS NOT GROUND HEIGHT LATER
        std::cout<<"position at fall: x "<< position.getX()<<" y "<<position.getY()<<std::endl;
        position.setY(300 - PLAYER_HEIGHT / 2);
        velocity.setY(0);
        std::cout<<"fell, reset location"<<std::endl;
    }

    auto hitbox = getHitbox() + position;
    auto level = gameLogic.getLevel();

    auto hitboxWidth = hitbox.getSize().getX();
    auto hitboxHeight = hitbox.getSize().getY();

    // Check the tiles in the level
    auto topY = floor(hitbox.getTopY() / 32);
    auto bottomY = floor(hitbox.getBottomY() / 32);
    auto leftX = floor(hitbox.getLeftX() / 32);
    auto rightX = floor(hitbox.getRightX() / 32);
    // std::cout<<"topY: "<<topY<<" bottomY: "<<bottomY<<" leftX: "<<leftX<<" rightX: "<<rightX<<std::endl;

    // Push the player out of a wall
    // if (velocity.getX() > 0) {
        for (auto y = topY; y <= bottomY-1; y++) {
            if (getCurrentDirection()==MoveDirection::RIGHT){
            auto collideWorld = level -> getWorldCollisionObject(Vector2(rightX, y));
            if (collideWorld) {
                std::cout<<"Right Collision Detected"<<std::endl;
                std::cout<<"X position"<< position.getX()<<" tile X; "<< collideWorld->bounds.x<<"player width" <<hitboxWidth<<" rightX *32 "<<rightX*32<<std::endl;
                // position.setX(collideWorld->bounds.x - hitboxWidth);
                position.setX((rightX*32)-(PLAYER_WIDTH/2));
                velocity.setX(0);

            }}
            else if (getCurrentDirection()==MoveDirection::LEFT){
            auto collideWorld = level -> getWorldCollisionObject(Vector2(leftX, y));
            if (collideWorld ){
                std::cout<<"Left Collision Detected"<<std::endl;
                std::cout<<"X position"<< position.getX()<<" tile X; "<< collideWorld->bounds.x+collideWorld->bounds.h<<"player width" <<hitboxWidth<<" leftX*32 "<<leftX*32<<std::endl;
                position.setX((leftX*32)+collideWorld->bounds.w+(PLAYER_WIDTH/2)-2);
                // position.setX(collideWorld->bounds.x+collideWorld->bounds.w+(PLAYER_WIDTH/2)+1);
                velocity.setX(0);

            }}
        }
    // }

    // Check bottom tiles
    for (auto x = leftX; x <= rightX; x++) {
        // if (level->colliderTileAt(Vector2(x, bottomY))) {
            auto collideWorld = level -> getWorldCollisionObject(Vector2(x, bottomY));

            if(collideWorld){
                auto collideLocal = level-> getLocalCollisionObject(Vector2(x,bottomY));
                std::cout<<"CW x: "<<collideWorld->bounds.x<<" y: "<<collideWorld->bounds.y<<" w: "<<collideWorld->bounds.w<<" h: "<<collideWorld->bounds.h<<std::endl;
                std::cout<<"CL x: "<<collideLocal->bounds.x<<" y: "<<collideLocal->bounds.y<<" w: "<<collideLocal->bounds.w<<" h: "<<collideLocal->bounds.h<<std::endl;
            // Push the player back out


                position.setY((bottomY * 32 - PLAYER_HEIGHT / 2)+ (collideLocal->bounds.y));


                velocity.setY(0);
                onGround=true;
                // Attempt a buffered jump
                if (bufferedJump) {
                    jump();
                }

                break;
            }
    }

    // Check ceiling tiles
    for (auto x = leftX; x <= rightX; x++) {
            auto collideWorld = level -> getWorldCollisionObject(Vector2(x, topY));
            if(collideWorld&& velocity.getY() < 0){
                auto collideLocal = level-> getLocalCollisionObject(Vector2(x,topY));
                std::cout<<"CW x: "<<collideWorld->bounds.x<<" y: "<<collideWorld->bounds.y<<" w: "<<collideWorld->bounds.w<<" h: "<<collideWorld->bounds.h<<std::endl;
                std::cout<<"CL x: "<<collideLocal->bounds.x<<" y: "<<collideLocal->bounds.y<<" w: "<<collideLocal->bounds.w<<" h: "<<collideLocal->bounds.h<<std::endl;

                if(hitbox.getTopY() <=(collideWorld->bounds.y+collideLocal->bounds.h)){
                    std::cout<<"Top Collision Detected"<<std::endl;
                    position.setY(collideWorld->bounds.y+collideLocal->bounds.h+PLAYER_HEIGHT/2);
                    velocity.setY(0.1);




            // Push the player back out
            // position.setY((topY + 1) * 32 + PLAYER_HEIGHT / 2);

            // velocity.setY(0.1); // Can't be 0, otherwise player can float on the ceiling

            break;}
                // }
        }
    }

    // // Check bottom tiles first
    // // To collide with the floor
    // // The player's bottom y coordinate must be greater than the floor tile's top y coordinate
    // for (auto x = leftX; x <= rightX; x++) {
    //     if (level->colliderTileAt(Vector2(x, bottomY))) {
    //         auto center = getHitboxCenter();
    //         auto playerY = center.getY();
    //         auto playerBottomY = playerY + hitboxHeight / 2;

    //         std::cout << position << ", " << playerBottomY << ", " << bottomY * 32 << std::endl;

    //         // Push the player back out
    //         position.setY(bottomY * 32 - hitboxHeight / 2);

    //         velocity.setY(0);

    //         // Attempt a buffered jump
    //         if (bufferedJump) {
    //             jump();
    //         }

    //         break;
    //     }
    // }

    // // Check ceiling tiles
    // for (auto x = leftX; x <= rightX; x++) {
    //     if (level->colliderTileAt(Vector2(x, topY))) {
    //         // Push the player back out
    //         position.setY((topY + 1) * 32 + hitboxHeight / 2);

    //         velocity.setY(0.1); // Can't be 0, otherwise player can float on the ceiling

    //         break;
    //     }
    // }

    // Check right tiles

    // for (auto y = topY; y <= bottomY; y++) {
    //     // Get updated player position
    //     auto center = getHitboxCenter();
    //     auto playerX = center.getX();
    //     auto playerY = center.getY();

    //     // This needs a more complex collision detector, we need to check if the box overlaps
    //     // First check is if the new y position is past the bottom bar
    //     // y here is the top-left position of the tile we are colliding with
    //     if (level->colliderTileAt(Vector2(rightX, y)) && playerY + hitboxHeight / 2 > y * 32 && playerY - hitboxHeight / 2 < y * 32) {
    //         std::cout << "Right collision" << std::endl;

    //         // Calculate the amount that gets collided

    //         // std::cout << topY << ", " << bottomY << std::endl;
    //         // std::cout << position << std::endl;
    //         // std::cout << "right collision at " << Vector2(rightX + 1, y) * 32 << " with offset " << hitbox.getOffset() << " and size " << hitbox.getSize() << std::endl;
    //         // Push the player back out
    //         position.setX(rightX * 32 - hitbox.getSize().getX() / 2 - 1);

    //         velocity.setX(0);

    //         break;
    //     }
    // }
}
