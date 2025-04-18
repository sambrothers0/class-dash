#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "Character.hpp"
#include "GameLogic.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"

const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 64;

class GameLogic;

class Enemy : public Character {

    private:
        // Set initial direction
        MoveDirection currentDirection = MoveDirection::RIGHT;

        // Last direction moved
        MoveDirection lastDirection = MoveDirection::RIGHT;

        int animationTicks = 0;

        double shooting_range; //the range at which the enemy begins shooting at the player
    public:
        explicit Enemy(Vector2 _position) : Character(_position) {velocity.setX(120);}

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        MoveDirection getLastDirection() const {
            return lastDirection;
        }

        int getCurrentAnimationOffset() const {
            return (animationTicks % 20) / 10;
        }

        virtual void move(double ms);

        virtual void shoot();

        // Enemy moves along a set predetermined track
        void moveOnTrack(double ms, const Vector2& pointA, const Vector2& pointB);

        // Moves the enemy in either direction
        void moveLeft();
        void moveRight();
};

#endif