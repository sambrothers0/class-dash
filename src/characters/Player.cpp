#include "characters/Player.hpp"

void Player::shoot() {
    
}

void Player::stopMoving() {
    velocity = Vector2(0, 0);
}

void Player::moveLeft() {
    velocity = Vector2(-250, 0);
}

void Player::moveRight() {
    velocity = Vector2(250, 0);
}