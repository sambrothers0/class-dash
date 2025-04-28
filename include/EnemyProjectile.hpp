#ifndef _ENEMYPROJECTILE_H
#define _ENEMYPROJECTILE_H

//#include "GameLogic.hpp"
//#include "Projectile.hpp"
//#include "characters/Player.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"
#include "MoveDirection.hpp"

#include <memory>



class EnemyProjectile {

    private:

        Vector2 currentPosition, velocity, startingPosition;
        Vector2 direction;
        bool active = false;

        MoveDirection currentDirection;

        double enemyProjTraveledDist = 0;
        BoundingBox hitbox = BoundingBox(Vector2(-7, -9), Vector2(14, 18));
        
    public:

    EnemyProjectile(Vector2 playerPosition, Vector2 enemyPosition, MoveDirection enemyDirection);
    // move projectile towards player
    
    void move(double ms);

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


    void setActive(bool activity) {;
        active = activity;
    }

    bool isActive() const {
        return active;
    }

    void setStartingPosition(MoveDirection direction);
    void setVelocity(double x, double y);
};

#endif