#ifndef _ENEMY_HPP
#define _ENEMY_HPP
#include "Character.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"

const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 64;

class Enemy : public Character {

    private:
        // Set initial direction
        MoveDirection currentDirection = MoveDirection::RIGHT;

        // Last direction moved
        MoveDirection lastDirection = MoveDirection::RIGHT;

        int animationTicks = 0;

        // Enemy hitbox dimensions
        BoundingBox hitbox = BoundingBox(Vector2(-5, -24), Vector2(20, 56));

        // Track the enemy moves on
        double trackStart, trackEnd;

        // y-level of the ground
        double groundLevel = 576;

        // Amount of health
        int health = 2;

        // Texture offset for the enemy (can be either 0 or 2 for now)
        int textureOffset = 0;

    public:
        explicit Enemy(Vector2 _position, double _trackStart, double _trackEnd) : Character(_position), trackStart(_trackStart), trackEnd(_trackEnd) {
            velocity.setX(120);
            textureOffset = rand() % 2 == 0 ? 0 : 2;
        }

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        MoveDirection getLastDirection() const {
            return lastDirection;
        }

        int getCurrentAnimationOffset() const {
            return (animationTicks % 20) / 10 + textureOffset;
        }

        void setGroundLevel(double _groundLevel) {
            groundLevel = _groundLevel;
            position.setY(_groundLevel);
        }

        BoundingBox getHitbox() const;

        virtual void move(double ms);

        virtual void shoot();

        // Enemy moves along a set predetermined track
        void moveOnTrack(double ms);

        // Moves the enemy in either direction
        void moveLeft();
        void moveRight();

        void decrementHealth() {
            health--;
        }

        bool isAlive() const {
            return health > 0;
        }

        int getTextureOffset() const {
            return textureOffset;
        }
};

#endif