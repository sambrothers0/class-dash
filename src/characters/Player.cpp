#include "characters/Player.hpp"
#include <iostream>
#include <cmath>
#include <vector>

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

    landed();

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
        newProjectile.setVelocity(-300, 0);
    } else if (currentDirection == MoveDirection::RIGHT) {
        newProjectile.setVelocity(300, 0);
    } else if (lastDirection == MoveDirection::LEFT) {
        newProjectile.setVelocity(-300, 0);
    } else {
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
    }
}

void Player::landed() {
    if (position.getY() >= GROUND_HEIGHT - PLAYER_HEIGHT / 2) { //THIS WILL NEED TO BE BASED ON COLLISIONS NOT GROUND HEIGHT LATER
        position.setY(GROUND_HEIGHT - PLAYER_HEIGHT / 2);
        velocity.setY(0);
    }
}

