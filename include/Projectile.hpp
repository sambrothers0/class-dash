#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "physics/Vector2.hpp"
#include "MoveDirection.hpp"

class Projectile {

    private:
        Vector2 currentPosition, velocity, startingPosition;
        bool active = false;

        // holds the current direction of the projectile, will be assigned players current direction
        MoveDirection currentDirection;
    public:
        Projectile(Vector2 playerPosition, MoveDirection playerDirection);

        Vector2 getPosition() const {
            return currentPosition;
        }

        Vector2 getStartingPosition() const {
            return startingPosition;
        }

        Vector2 getVelocity() const {
            return velocity;
        }

        void setActive(bool activity) {
            active = activity;
        }

        bool isActive() {
            return active;
        }

        void setVelocity(double x, double y);
        void move(double ms);

};

#endif