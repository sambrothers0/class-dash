#include "characters/Enemy.hpp"

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {

}

void Enemy::moveOnTrack(double ms, Vector2 pointA, Vector2 pointB) {

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