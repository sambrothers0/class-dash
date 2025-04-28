#include "characters/Enemy.hpp"
#include <iostream>
#include "characters/Player.hpp"


void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {
    // shoots a projectile at the player
    EnemyProjectile projectile = EnemyProjectile(playerLoc, position, currentDirection);
    enemyProjectile = std::make_shared<EnemyProjectile>(projectile);

    if (currentDirection == MoveDirection::LEFT) {
        enemyProjectile->setStartingPosition(currentDirection);
        enemyProjectile->setVelocity(-300, 0);
    } else if (currentDirection == MoveDirection::RIGHT) {
        enemyProjectile->setStartingPosition(currentDirection);
        enemyProjectile->setVelocity(300, 0);
    } else if (lastDirection == MoveDirection::LEFT) {
        enemyProjectile->setStartingPosition(lastDirection);
        enemyProjectile->setVelocity(-300, 0);
    } else {
        enemyProjectile->setStartingPosition(MoveDirection::RIGHT);
        enemyProjectile->setVelocity(300, 0);
    }

}

void Enemy::moveOnTrack(double ms) {
    // Made it to the left end of the track
    if (currentDirection == MoveDirection::NONE) {
        velocity.setX(0);
        return;
    }
    if (position.getX() <= trackStart) {
        moveRight();
    }
    // Made it to the right end of the track
    else if (position.getX() >= trackEnd) {
        moveLeft();
    }
    
    // Placeholder until collision added ------
    if (position.getY() >= groundLevel) {
        velocity.setY(0);
        position.setY(groundLevel);
    }
    //------------

    Character::move(ms);
    animationTicks++;

    if (enemyProjectile && enemyProjectile->isActive()) {
        enemyProjectile->move(ms);
    }

}

void Enemy::moveToPlayer(std::shared_ptr<Player> player) {
    // move to player within track range
    //playerLoc = player->getPosition();
    
    if (playerLoc.getX() <= getPosition().getX()) {
        if (position.getX() == (trackStart + 5)) {
            //position.setX(trackStart + 5);
            currentDirection = MoveDirection::NONE;
        }
        else
            moveLeft();
    }
    else {
        if (position.getX() == (trackEnd - 5)) {
            //position.setX(trackEnd - 5);
            currentDirection = MoveDirection::NONE;
        }
        else 
            moveRight();
    }
   
}

bool Enemy::detectPlayer(std::shared_ptr<Player> player, double ms) {
   // check if player is in range
   playerLoc = player->getPosition();
   Vector2 difference = playerLoc - getPosition();

   //check if x axis in range
   if ((difference.getX() >= -detectRange) && (difference.getX() < detectRange)) {
       //check if y axis is in range
       if ((difference.getY() >= -detectRange) && (difference.getY() < detectRange)) {
           // when in range move to player and shoot
           moveToPlayer(player);
           //if (!enemyProjectile->isActive()) {
            //shoot();
           //}
           return true;
       }
   } 
   return false;
   // if not in range, continue its track  
   //else {
    //moveOnTrack(ms);
   //}
}

BoundingBox Enemy::getHitbox() const {
    // The hitbox is different if the enemy is flipped
    if (lastDirection == MoveDirection::RIGHT) {
        return hitbox;
    } else {
        auto oldOffset = hitbox.getOffset();

        return BoundingBox(
            Vector2(-12, oldOffset.getY()), // -12 is a magic number here, but it is the correct offset for flipping the enemy sprite
            hitbox.getSize()
        );
    }
}

void Enemy::moveLeft() {
    velocity.setX(-120);
    currentDirection = MoveDirection::LEFT;
    lastDirection = MoveDirection::LEFT;
}

void Enemy::moveRight() {
    velocity.setX(120);
    currentDirection = MoveDirection::RIGHT;
    lastDirection = MoveDirection::RIGHT;
}

std::shared_ptr<EnemyProjectile> Enemy::getEnemyProjectile() {
    if (enemyProjectile && enemyProjectile->isActive()) {
        return enemyProjectile;
    }
    return enemyProjectile;
}