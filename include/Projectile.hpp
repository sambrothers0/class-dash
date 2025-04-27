#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "physics/Vector2.hpp"
#include "MoveDirection.hpp"
#include "GameLogic.hpp"
#include <memory>

class Projectile {

    protected:
        // Apparently push_back does not work when a member variable is a reference, so I switched it to a pointer
        std::shared_ptr<GameLogic> gameLogic;

        Vector2 currentPosition, velocity, startingPosition;
        bool active = false;

        // holds the current direction of the projectile, will be assigned players current direction
        MoveDirection currentDirection;

        BoundingBox hitbox = BoundingBox(Vector2(-7, -9), Vector2(14, 18));
    public:
        Projectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 playerPosition, MoveDirection playerDirection);

        const Vector2& getPosition() const {
            return currentPosition;
        }

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        const Vector2& getStartingPosition() const {
            return startingPosition;
        }

        const Vector2& getVelocity() const {
            return velocity;
        }

        const BoundingBox& getHitbox() const {
            return hitbox;
        }

        void setActive(bool activity) {
            active = activity;
        }

        bool isActive() {
            return active;
        }

        void setStartingPosition(MoveDirection direction);
        void setVelocity(double x, double y);
        virtual void move(double ms);

        void setDirection(MoveDirection direction) {
            currentDirection = direction;
        }

};

#endif