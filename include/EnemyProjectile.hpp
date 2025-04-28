#ifndef _ENEMYPROJECTILE_H
#define _ENEMYPROJECTILE_H

//#include "GameLogic.hpp"
//#include "Projectile.hpp"
//#include "characters/Player.hpp"
#include "physics/Vector2.hpp"
#include "MoveDirection.hpp"

#include <memory>



class EnemyProjectile {

    private:

        Vector2 currentPosition, destination, velocity, startingPosition;
        bool active = false;

        MoveDirection currentDirection;

        double enemyProjTraveledDist = 0;
        
    public:

    EnemyProjectile(Vector2 playerPosition, Vector2 enemyPosition, MoveDirection enemyDirection);
    // move projectile towards player
    
    void move(double ms);

    const Vector2& getPosiiton() const {
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

    

    void setActive(bool activity) {
        active = activity;
    }

    bool isActive() {
        return active;
    }

    void setStartingPosition(MoveDirection direction);
    void setVelocity(double x, double y);
};

#endif