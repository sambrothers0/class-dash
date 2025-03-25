#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"
#include "MoveDirection.hpp"
#include "Projectile.hpp"

#include <deque>

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

// Number of projectiles that can be active at once
const int MAX_PROJECTILES = 5;

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection = MoveDirection::NONE;

    // Last direction moved in
    MoveDirection lastDirection = MoveDirection::RIGHT;
    
    // List of available projectiles
    std::deque<Projectile> projectiles;

    // Which animation frame to use (track how many ticks the current movement has occurred for)
    int animationTicks = 0;

    public:
    Player(Vector2 _position) : Character(_position) {}

    MoveDirection getCurrentDirection() const {
        return currentDirection;
    }

    std::deque<Projectile>& getProjectiles() {
        return projectiles;
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