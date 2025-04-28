#ifndef _ENEMYPROJECTILE_H
#define _ENEMYPROJECTILE_H

//#include "GameLogic.hpp"
//#include "Projectile.hpp"
//#include "characters/Player.hpp"
#include "physics/Vector2.hpp"
#include "physics/BoundingBox.hpp"
#include "MoveDirection.hpp"

#include <memory>

class GameLogic;



class EnemyProjectile {

    private:
        std::shared_ptr<GameLogic> gameLogic;
        Vector2 currentPosition;
        Vector2 direction;
        bool active = false;

        double enemyProjTraveledDist = 0;
        BoundingBox hitbox = BoundingBox(Vector2(-7, -9), Vector2(14, 18));
        
    public:

    EnemyProjectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 playerPosition, Vector2 enemyPosition);
    // move projectile towards player
    
    void move(double ms);

    const Vector2& getPosition() const {
        return currentPosition;
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

    bool isMovingLeft() const {
        return direction.getX() < 0;
    }
};

#endif