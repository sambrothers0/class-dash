#include "characters/Enemy.hpp"

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {

}

void Enemy::moveOnTrack(double ms, Vector2 pointA, Vector2 pointB) {
    // Made it to the left end of the track
    if (position.getX() == pointA.getX()) {
        moveRight();
    }
    // Made it to the right end of the track
    else if (position.getX() == pointB.getX()) {
        moveLeft();
    }
    else {
        Character::move(ms);
    }
}

void Enemy::moveLeft() {
    velocity.setX(-150);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
}

void Enemy::moveRight() {
    velocity.setX(150);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
}