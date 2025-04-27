#ifndef _CORGI_HPP
#define _CORGI_HPP
#include "Character.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"

const int CORGI_WIDTH = 32;
const int CORGI_HEIGHT = 64;

class Corgi : public Character {

    private:
        // Set initial direction
        MoveDirection currentDirection = MoveDirection::RIGHT;

        // Last direction moved
        MoveDirection lastDirection = MoveDirection::RIGHT;

        int animationTicks = 0;

        // corgi hitbox dimensions
        BoundingBox hitbox = BoundingBox(Vector2(-16, 0), Vector2(32, 19));

        // Track the corgi moves on
        double trackStart, trackEnd;

        // y-level of the ground
        double groundLevel = 576;

        // Texture offset for the CORGI (can be either 0 or 2 for now)
        int textureOffset = 0;

    public:
        Corgi(Vector2 _position, double _trackStart, double _trackEnd) : Character(_position), trackStart(_trackStart), trackEnd(_trackEnd) {
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

        virtual void shoot() {}

        // CORGI moves along a set predetermined track
        void moveOnTrack(double ms);

        // Moves the CORGI in either direction
        void moveLeft();
        void moveRight();

        int getTextureOffset() const {
            return textureOffset;
        }
};

#endif