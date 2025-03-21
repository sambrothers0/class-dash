#include "characters/Player.hpp"
#include <iostream>
#include <cmath>

const int GROUND_HEIGHT = 600; //This is just the current ground height based on how player position is called in GameLogic
const float JUMP_HEIGHT = 100.0f; 
const int HEIGHT = 64;
const int WIDTH = 32;

void Player::move(double ms) {
    Character::move(ms);

    landed();
}

void Player::shoot() {
    
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
    if (position.getY() >= GROUND_HEIGHT - HEIGHT / 2) { //THIS WILL NEED TO BE BASED ON COLLISIONS NOT GROUND HEIGHT LATER
        position.setY(GROUND_HEIGHT - HEIGHT / 2);
        velocity.setY(0);
    }
}

