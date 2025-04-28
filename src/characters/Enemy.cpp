#include "characters/Enemy.hpp"
#include <iostream>

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {
    // shoots a projectile at the player

}

void Enemy::moveOnTrack(double ms) {
    // Made it to the left end of the track
    if (position.getX() <= trackStart) {
        moveRight();
    }
    // Made it to the right end of the track
    else if (position.getX() >= trackEnd) {
        moveLeft();
    }
    
    // Placeholder until collision added ------
    if (position.getY() >= groundLevel) {
        velocity.setY(0);
        position.setY(groundLevel);
    }
    //------------

    Character::move(ms);
    animationTicks++;
    
}

void Enemy::moveToPlayer() {
    // move to player within track range
}

void Enemy::detectPlayer() {
    // check if player is in range

    // when in range move to player and shoot
}

BoundingBox Enemy::getHitbox() const {
    // The hitbox is different if the enemy is flipped
    if (lastDirection == MoveDirection::RIGHT) {
        return hitbox;
    } else {
        auto oldOffset = hitbox.getOffset();

        return BoundingBox(
            Vector2(-12, oldOffset.getY()), // -12 is a magic number here, but it is the correct offset for flipping the enemy sprite
            hitbox.getSize()
        );
    }
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