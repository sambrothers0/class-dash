#include "characters/Enemy.hpp"
#include <iostream>
#include "characters/Player.hpp"

void Enemy::move(double ms) {
    Character::move(ms);
}

void Enemy::shoot() {
    // shoots a projectile at the player

}

void Enemy::moveOnTrack(std::shared_ptr<Player> player, double ms) {
    // Made it to the left end of the track

    if (inRange(player)){
        //move towards player if in range
        moveToPlayer(player, ms);
    }
    else{ //move on predetermined track
    if (position.getX() <= trackStart) {
        moveRight();
    }
    // Made it to the right end of the track
    else if (position.getX() >= trackEnd) {
        moveLeft();
    }
}    if (currentDirection == MoveDirection::NONE) {
        velocity.setX(0);
        return;
    }
    // Placeholder until collision added ------
    if (position.getY() >= groundLevel) {
        velocity.setY(0);
        position.setY(groundLevel);
    }
    //------------

    Character::move(ms);
    animationTicks++;
    
}

void Enemy::moveToPlayer(std::shared_ptr<Player> player, double ms) {
    playerLoc = player->getPosition();
    auto diff = playerLoc - position;
    // if in range but still far enough away, walk towards player
    if (abs(diff.getX()) > 10) {  
        if (playerLoc.getX() < position.getX() && position.getX()>trackStart) {
            moveLeft();
        } else if (playerLoc.getX() > position.getX() && position.getX()<trackEnd)  {
            moveRight();
        }
    } else {
        // if directly next to player, stop
        currentDirection = MoveDirection::NONE;
    }
}

bool Enemy::inRange(std::shared_ptr<Player> player) {
    playerLoc = player->getPosition();
    auto difference = abs(playerLoc.getX() - getPosition().getX());
    auto ydiff= abs(playerLoc.getY() - getPosition().getY());
    if (difference <= detectRange && ydiff <= ENEMY_HEIGHT){
        return true;
    }
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