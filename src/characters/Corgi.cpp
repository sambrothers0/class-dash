#include "characters/Corgi.hpp"

void Corgi::move(double ms) {
    Character::move(ms);
}

void Corgi::moveOnTrack(double ms) {
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

BoundingBox Corgi::getHitbox() const {
    return hitbox;
}

void Corgi::moveLeft() {
    velocity.setX(-120);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
}

void Corgi::moveRight() {
    velocity.setX(120);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
}