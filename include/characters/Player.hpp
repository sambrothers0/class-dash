#ifndef _PLAYER_H
#define _PLAYER_H

#include "Character.hpp"
#include "MoveDirection.hpp"
#include "Projectile.hpp"

class Player : public Character {
    private:
    // Current direction of movement
    MoveDirection currentDirection;
    //Previous direction of movement, used for projectiles
    MoveDirection previousDirection;

    public:
    Player(Vector2 _position) : Character(_position), projectile(_position, currentDirection), previousDirection(MoveDirection::RIGHT) {}
    
    Projectile projectile;

    MoveDirection getCurrentDirection() const {
        return currentDirection;
    }

    Projectile getProjectile() {
        return projectile;
    }

    virtual void move(double ms);

    virtual void shoot();

    // Stops the movement of the player
    void stopMoving();

    // Move the player in either direction
    void moveLeft();
    void moveRight();
    void jump();
    void landed();
};

#endif