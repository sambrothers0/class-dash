#include "characters/Player.hpp"
#include <iostream>
#include <cmath>

const int GROUND_HEIGHT = 600; //This is just the current ground height based on how player position is called in GameLogic
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

    // Move the projectile if needed
    if (projectile.isActive()) {
        projectile.move(ms);
    }
}

void Player::shoot() {
    projectile = Projectile(position, currentDirection);
    projectile.setActive(true);

    if (currentDirection == MoveDirection::LEFT) {
        projectile.setVelocity(-300, 0);
    } else if (currentDirection == MoveDirection::RIGHT) {
        projectile.setVelocity(300, 0);
    } else if (lastDirection == MoveDirection::LEFT) {
        projectile.setVelocity(-300, 0);
    } else {
        projectile.setVelocity(300, 0); 
    }
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

