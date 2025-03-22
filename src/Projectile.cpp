#include "Projectile.hpp"

Projectile::Projectile(Vector2 playerPosition, MoveDirection playerDirection) 
    : currentDirection(playerDirection) {
    position.setX(playerPosition.getX() + 20);
    position.setY(playerPosition.getY());
}

// move the projectile along the x axis
void Projectile::move(double ms) {
    double seconds = ms/1000;
    double moveOffset = position.getX() + velocity.getX() * seconds;
    position.setX(moveOffset);
    
}