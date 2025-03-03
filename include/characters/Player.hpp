#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"

class Player : public Character {
    public:
    Player(Vector2 _position) : Character(_position) {}

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