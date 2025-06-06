#include "characters/Enemy.hpp"
#include <iostream>
#include "characters/Player.hpp"
#include <vector>
#include <cmath>


std::deque<EnemyProjectile> enemyProjectiles;
SDL_TimerID enemyProjectileTimerID;
bool isEnemyProjectileTimerActive = false;

void Enemy::move(double ms) {
    Character::move(ms);
}

// Callback for the projectile timer
Uint32 onEnemyProjectileTimer(Uint32 interval, void *param) {
    auto* enemy = reinterpret_cast<Enemy*>(param);

    enemy->setIfProjectileTimerActive(false);

    return 0; // Don't repeat
}

void Enemy::shoot() {

    if (!canShoot) {
        return;
    }

    if (isEnemyProjectileTimerActive) {
        return;
    }

    // shoots a projectile at the player
    EnemyProjectile enemyProjectile = EnemyProjectile(std::make_shared<GameLogic>(gameLogic), playerLoc, position);

    // Add to the list of projectiles if there aren't already too many
    if (enemyProjectiles.size() < MAX_ENEMY_PROJECTILES) {
        enemyProjectiles.push_back(enemyProjectile);
    }

    // Set up the projectile timer
    isEnemyProjectileTimerActive = true;
    enemyProjectileTimerID = SDL_AddTimer(ENEMY_PROJECTILE_DELAY, onEnemyProjectileTimer, this);

}

void Enemy::moveOnTrack(double ms) {
    //moving = true;
    
    if (currentDirection == MoveDirection::NONE) {
        velocity.setX(0);
        moving = false;
        return;
    }
    
    // Made it to the left end of the track
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
    if (moving) {
        animationTicks++;
    }
}

void Enemy::moveToPlayer(std::shared_ptr<Player> player) {
    // if really close to player, stop walking
    if (abs(playerLoc.getX() - getPosition().getX()) <= 50) {
        currentDirection = MoveDirection::NONE;
        velocity.setX(0);
        moving = false;
        return;
    }
    // if at the ends of the track while following, stop
    else if (playerLoc.getX() <= getPosition().getX()) {
        if (abs(position.getX() - trackStart) <= 5) {
            currentDirection = MoveDirection::NONE;
            velocity.setX(0);
            moving = false;
            return;
        }
        else {
            moveLeft();
            moving = true;
            return;
        }
    }
    else { 
        if (abs(position.getX() - trackEnd) <= 5) {
            currentDirection = MoveDirection::NONE;
            velocity.setX(0);
            moving = false;
            return;
        }
        else {
            moveRight();
            moving = true;
            return;
        }
    }
    moving = true;
}

bool Enemy::detectPlayer(std::shared_ptr<Player> player, double ms) {
    if (!canShoot) {
        return false; // the enemy is blind
    }

   // check if player is in range
   playerLoc = player->getPosition();
   Vector2 difference = playerLoc - getPosition();

   //check if x axis in range
   if ((difference.getX() >= -detectRange) && (difference.getX() < detectRange)) {
       //check if y axis is in range
       if ((difference.getY() >= -detectRange) && (difference.getY() < detectRange)) {
           // when in range move to player and shoot
           moveToPlayer(player);
           shoot();
           return true;
       }
   } 
   moveOnTrack(ms);
   return false;
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
// Switch Directions on path
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


void Enemy::updateProjectiles(double ms) {
    // Move the projectiles, while marking any which should be deleted
    std::vector<size_t> toDelete;

    for (size_t idx = 0; idx < enemyProjectiles.size(); idx++) {
        auto& proj = enemyProjectiles[idx];

        if (proj.isActive()) {
            proj.move(ms);
        } else {
            toDelete.push_back(idx);
        }
    }

    // Delete the corresponding indexes
    if (toDelete.size() > 0) {
        // This is needed to keep the indexes accurate
        int deleted = 0;

        for (auto idx : toDelete) {
            enemyProjectiles.erase(enemyProjectiles.begin() + idx - deleted);
            deleted++;
        }
    }
}