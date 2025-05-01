#ifndef _ENEMY_H
#define _ENEMY_H

#include "Character.hpp"
#include "MoveDirection.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"
#include <memory>
#include "EnemyProjectile.hpp"
#include <deque>
#include "SDL.h"
//#include "characters/Player.hpp"

class Player;

const int ENEMY_WIDTH = 32;
const int ENEMY_HEIGHT = 64;

// Number of projectiles that can be active at once
const int MAX_ENEMY_PROJECTILES = 2;

// Delay for shooting projectiles in ms
const int ENEMY_PROJECTILE_DELAY = 1000;

class GameLogic;

class Enemy : public Character {

    private:
        GameLogic& gameLogic;

        // There is a delay between shooting projectiles
        SDL_TimerID enemyProjectileTimerId;
        bool isEnemyProjectileTimerActive = false; //= false;

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

        Vector2 playerLoc; 

        double detectRange = 200;

        std::shared_ptr<EnemyProjectile> enemyProjectile;
        
         // List of available projectiles
        std::deque<EnemyProjectile> enemyProjectiles;

        // Texture offset for the enemy (can be either 0 or 2 for now)
        int textureOffset = 0;

        bool canShoot = false; // Shoots and follows the player

        bool moving = true; // checks if the enemy is moving, if so update animation ticks

    public:
        explicit Enemy(GameLogic& _gameLogic, Vector2 _position, double _trackStart, double _trackEnd, bool _canShoot) : Character(_position), gameLogic(_gameLogic), trackStart(_trackStart), trackEnd(_trackEnd), canShoot(_canShoot) {
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

        void moveToPlayer(std::shared_ptr<Player> player);

        bool detectPlayer(std::shared_ptr<Player> player, double ms);

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

        //std::shared_ptr<EnemyProjectile> getEnemyProjectile();

        const std::deque<EnemyProjectile>& getProjectiles() const {
            return enemyProjectiles;
        }

        // Sets if the projectile timer is active
        void setIfProjectileTimerActive(bool active) {
            isEnemyProjectileTimerActive = active;
        }

        int getTextureOffset() const {
            return textureOffset;
        }

        void updateProjectiles(double ms);

        bool getCanShoot(){
            return canShoot;
        }
};

#endif