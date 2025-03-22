#include "characters/Player.hpp"
#include <iostream>
#include <cmath>

const int GROUND_HEIGHT = 600; //This is just the current ground height based on how player position is called in GameLogic
const float JUMP_HEIGHT = 100.0f; 

void Player::move(double ms) {
    Character::move(ms);

    landed();
}

void Player::shoot() {
    projectile = Projectile(position, currentDirection);
    projectile.setActive(true);

    if (currentDirection == MoveDirection::LEFT) {
        projectile.getVelocity().setX(-300);
    }
    else if (currentDirection == MoveDirection::RIGHT) {
        projectile.getVelocity().setX(300);
    }
    
    /*
    for (int i = 0; i != 10; i++) {
        double previousX = projectile.getPosition().getX();
        projectile.getPosition().setX(previousX + 20); 
    }

    projectile.setActive(false);
    */
}

void Player::stopMoving() {
    velocity.setX(0);
    currentDirection = MoveDirection::NONE;
    // velocity = Vector2(0, 0);
}

void Player::moveLeft() {
    velocity.setX(-250);
    currentDirection = MoveDirection::LEFT;
    // velocity = Vector2(-250, 0);
}

void Player::moveRight() {
    velocity.setX(250);
    currentDirection = MoveDirection::RIGHT;
    // velocity = Vector2(250, 0);
}

void Player::jump() {
    if (velocity.getY() == 0) {
        velocity.setY(-500);
    }
}

void Player::landed() {
    if (position.getY() >= GROUND_HEIGHT - 20) { //THIS WILL NEED TO BE BASED ON COLLISIONS NOT GROUND HEIGHT LATER
        position.setY(GROUND_HEIGHT - 20);
        velocity.setY(0);
    }
}

