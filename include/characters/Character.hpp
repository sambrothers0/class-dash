#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "physics/Vector2.hpp"

class Character {
    protected:
    Vector2 position, velocity; // Velocity unit is in pixels per second

    public:
    Character(Vector2 _position) : position(_position), velocity(Vector2(0, 0)) {}

    Vector2 getPosition() const {
        return position;
    }

    Vector2 getVelocity() const {
        return velocity;
    }

    void move(double ms);

    virtual void shoot() = 0;

    virtual ~Character() = 0;
};

#endif