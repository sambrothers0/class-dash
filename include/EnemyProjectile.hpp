#ifndef _ENEMYPROJECTILE_H
#define _ENEMYPROJECTILE_H

#include "GameLogic.hpp"
#include "Projectile.hpp"


class EnemyProjectile : public Projectile {

    private:

    public:

    EnemyProjectile(std::shared_ptr<GameLogic> _gameLogic, Vector2 enemyPosition, MoveDirection enemyDirection) : Projectile(_gameLogic, enemyPosition, enemyDirection) {}

    // move projectile towards player
    virtual void move(double ms);

};

#endif