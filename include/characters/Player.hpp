#ifndef _PLAYER_H
#define _PLAYER_H

#include "SDL.h"
#include "Character.hpp"
#include "MoveDirection.hpp"
#include "Projectile.hpp"

#include <deque>

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

// Number of projectiles that can be active at once
const int MAX_PROJECTILES = 5;

// Delay for shooting projectiles in ms
const int PROJECTILE_DELAY = 500;

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection = MoveDirection::NONE;

    // Last direction moved in
    MoveDirection lastDirection = MoveDirection::RIGHT;
    
    // List of available projectiles
    std::deque<Projectile> projectiles;

    // There is a delay between shooting projectiles
    SDL_TimerID projectileTimerId;
    bool isProjectileTimerActive = false;

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

    // Sets if the projectile timer is active
    void setIfProjectileTimerActive(bool active) {
        isProjectileTimerActive = active;
    }
};

#endif