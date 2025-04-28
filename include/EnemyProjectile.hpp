#ifndef _ENEMYPROJECTILE_H
#define _ENEMYPROJECTILE_H

#include "GameLogic.hpp"
#include "Projectile.hpp"
#include "characters/Player.hpp"


class EnemyProjectile : public Projectile {

    private:
        Vector2 destination;

        double enemyProjTraveledDist = 0;
    public:

    EnemyProjectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 enemyPosition, MoveDirection enemyDirection) : Projectile(_gameLogic, enemyPosition, enemyDirection) {
        destination = gameLogic->getPlayer()->getPosition();
    }

    // move projectile towards player
    virtual void move(double ms);

};

#endif