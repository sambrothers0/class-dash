#ifndef _PLAYER_H
#define _PLAYER_H

#include "SDL.h"
#include "Character.hpp"
#include "GameLogic.hpp"
#include "MoveDirection.hpp"
#include "Projectile.hpp"
#include "physics/BoundingBox.hpp"
#include "physics/Vector2.hpp"

#include <deque>

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

// Number of projectiles that can be active at once
const int MAX_PROJECTILES = 5;

// Delay for shooting projectiles in ms
const int PROJECTILE_DELAY = 250;

class GameLogic;

class Player : public Character {
    private:
    GameLogic& gameLogic;

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

    // Player hitbox dimensions
    BoundingBox hitbox = BoundingBox(Vector2(-5, -24), Vector2(20, 56));

    // Jump buffering mechanic lets you hold down the jump key to jump as soon as you land
    bool bufferedJump = false;
    
    bool onGround=false;
    bool falling=true;
    double fallHeight;

    bool isJumping=false;

    // Handles any floor collisions
    void handleFloorCollisions();
    void handleCeilingCollisions();

    void handleRightCollisions();
    void handleLeftCollisions();

    // Detects collisions with the enemy
    void handleEnemyCollisions();

    public:
    Player(GameLogic& _gameLogic, Vector2 _position) : Character(_position), gameLogic(_gameLogic), fallHeight(_position.getY() + PLAYER_HEIGHT / 2.0) {}

    MoveDirection getCurrentDirection() const {
        return currentDirection;
    }

    MoveDirection getLastDirection() const {
        return lastDirection;
    }

    const std::deque<Projectile>& getProjectiles() const {
        return projectiles;
    }

    int getCurrentAnimationOffset() const;

    BoundingBox getHitbox() const;

    // Gets the center of the hitbox
    Vector2 getHitboxCenter() const;

    virtual void move(double ms);

    virtual void shoot();

    // Stops the movement of the player
    void stopMoving();

    // Move the player in either direction
    void moveLeft();
    void moveRight();
    void jump();
    void handleCollisions();

    // Sets if the projectile timer is active
    void setIfProjectileTimerActive(bool active) {
        isProjectileTimerActive = active;
    }

    void setBufferedJump(bool jump) {
        bufferedJump = jump;
    }
};

#endif