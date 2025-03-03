#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"
#include "MoveDirection.hpp"

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection;

    public:
    Player(Vector2 _position) : Character(_position) {}

    MoveDirection getCurrentDirection() const {
        return currentDirection;
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