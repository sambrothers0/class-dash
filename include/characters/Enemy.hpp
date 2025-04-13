#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "Character.hpp"
#include "GameLogic.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"

class Enemy : public Character {

    private:
        // Reference to the game logic
        GameLogic& gameLogic;

        // Set initial direction
        MoveDirection currentDirection = MoveDirection::NONE;

        // Last direction moved
        MoveDirection lastDirection = MoveDirection::RIGHT;
    public:
        Enemy(GameLogic& _gameLogic, Vector2 _position) : gameLogic(_gameLogic), Character(_position) {}

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        MoveDirection getLastDirection() const {
            return lastDirection;
        }

        virtual void move(double ms);

        virtual void shoot();

        // Enemy moves along a set predetermined track
        void moveOnTrack(double ms, Vector2 pointA, Vector2 pointB);

        // Moves the enemy in either direction
        void moveLeft();
        void moveRight();
};

#endif