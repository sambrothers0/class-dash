#ifndef _Powerup_HPP
#define _Powerup_HPP
#include "Character.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"

const int POWERUP_WIDTH = 32;
const int POWERUP_HEIGHT = 64;

class Powerup : public Character {

    private:
        // Set initial direction
        MoveDirection currentDirection = MoveDirection::RIGHT;

        // Last direction moved
        MoveDirection lastDirection = MoveDirection::RIGHT;

        int animationTicks = 0;

        // Powerup hitbox dimensions
        BoundingBox hitbox = BoundingBox(Vector2(-10, -10), Vector2(20, 25));

        // both set to the same value
        double trackStart, trackEnd;

        // y-level of the ground
        double groundLevel = 576;

        // Texture offset for the Powerup (can be either 0 or 2 for now)
        int textureOffset = 0;

        // indicates if the powerup is still on the screen
        bool active = true;

    public:
        Powerup(Vector2 _position, double _trackStart, double _trackEnd) : Character(_position), trackStart(_trackStart), trackEnd(_trackEnd) {}

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        MoveDirection getLastDirection() const {
            return lastDirection;
        }
        int getCurrentAnimationOffset() const;


        void setGroundLevel(double _groundLevel) {
            groundLevel = _groundLevel;
            position.setY(_groundLevel);
        }

        BoundingBox getHitbox() const;

        virtual void move(double ms);

        virtual void shoot() {}

        void animate();


        int getTextureOffset() const {
            return textureOffset;
        }

        // returns activation status
        bool isActive() {
            return active;
        }

        // deactivates a powerup for cleanup
        void deactivate() {
            active = false;
        }
};

#endif