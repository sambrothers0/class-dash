#include "characters/Enemy.hpp"
#include <iostream>

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {

}

void Enemy::moveOnTrack(double ms, const Vector2& pointA, const Vector2& pointB) {
    // Made it to the left end of the track
    if (position.getX() <= pointA.getX()) {
        moveRight();
    }
    // Made it to the right end of the track
    else if (position.getX() >= pointB.getX()) {
        moveLeft();
    }
    
    // Placeholder until collision added ------
    if (position.getY() >= 580) {
        velocity.setY(0);
        position.setY(580);
    }
    //------------

    Character::move(ms);
    animationTicks++;
    
}

void Enemy::moveLeft() {
    velocity.setX(-120);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
}

void Enemy::moveRight() {
    velocity.setX(120);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
}