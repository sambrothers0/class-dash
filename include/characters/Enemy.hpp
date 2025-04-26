#ifndef _ENEMY_H
#define _ENEMY_H

#include "Character.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"
//#include "Projectile.hpp"
//#include "../GameLogic.hpp"
#include "SDL.h"
#include <memory>
#include <deque>
//#include "characters/Player.hpp"

class GameLogic;
class Player;
class Projectile;

const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 64;

// Number of projectiles that can be active at once
//const int MAX_PROJECTILES = 1;

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

        // players current location
        Vector2 playerLoc; 

        // range for enemy following and shooting
        double detectRange = 200;

        bool projActive = false;
        // List of available projectiles
        //std::deque<Projectile> projectiles;

        std::shared_ptr<Projectile> enemyProj;

       

    // There is a delay between shooting projectiles
    SDL_TimerID projectileTimerId;
    bool isProjectileTimerActive = false;

    public:
        explicit Enemy(Vector2 _position, double _trackStart, double _trackEnd) : Character(_position), trackStart(_trackStart), trackEnd(_trackEnd) {
            velocity.setX(120);
             // List of available projectiles
            //std::deque<Projectile> projectiles;
        }

        MoveDirection getCurrentDirection() const {
            return currentDirection;
        }

        MoveDirection getLastDirection() const {
            return lastDirection;
        }

        int getCurrentAnimationOffset() const {
            return (animationTicks % 20) / 10;
        }

        void setGroundLevel(double _groundLevel) {
            groundLevel = _groundLevel;
            position.setY(_groundLevel);
        }

        BoundingBox getHitbox() const;

        virtual void move(double ms);

        void moveToPlayer(std::shared_ptr<Player> player);

        bool detectPlayer(std::shared_ptr<Player> player, double ms);

        virtual void shoot();

        void shoot(std::shared_ptr<GameLogic> gameLogic);

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
};

#endif