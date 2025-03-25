#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"
#include "MoveDirection.hpp"
#include "Projectile.hpp"

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection = MoveDirection::NONE;

    // Last direction moved in
    MoveDirection lastDirection = MoveDirection::RIGHT;
    
    Projectile projectile;

    // Which animation frame to use (track how many ticks the current movement has occurred for)
    int animationTicks = 0;

    public:
    Player(Vector2 _position) : Character(_position), projectile(_position, currentDirection) {}

    MoveDirection getCurrentDirection() const {
        return currentDirection;
    }

    Projectile& getProjectile() {
        return projectile;
    }

    MoveDirection getLastDirection() const {
        return lastDirection;
    }

    int getCurrentAnimationOffset() const;

    virtual void move(double ms);

    virtual void shoot();

    // Stops the movement of the player
    void stopMoving();

    // Move the player in either direction
    void moveLeft();
    void moveRight();
    void jump();
    void landed();
};

#endif