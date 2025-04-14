#include "characters/Enemy.hpp"

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {

}

void Enemy::moveOnTrack(double ms, Vector2 pointA, Vector2 pointB) {
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
        //position.setY(position.getY()-1);
    }
    //------------

    Character::move(ms);
    
}

void Enemy::moveLeft() {
    velocity.setX(-100);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
}

void Enemy::moveRight() {
    velocity.setX(100);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
}