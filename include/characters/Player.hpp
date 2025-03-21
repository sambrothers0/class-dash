#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"
#include "MoveDirection.hpp"

const int PLAYER_WIDTH = 32;
const int PLAYER_HEIGHT = 64;

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection;

    // Last direction moved in
    MoveDirection lastDirection;

    public:
    Player(Vector2 _position) : Character(_position) {}

    MoveDirection getCurrentDirection() const {
        return currentDirection;
    }

    MoveDirection getLastDirection() const {
        return lastDirection;
    }

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