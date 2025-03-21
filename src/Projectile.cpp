#include "Projectile.hpp"

Projectile::Projectile(Vector2 playerPosition, MoveDirection playerDirection) 
    : currentDirection(playerDirection) {
    position.setX(playerPosition.getX() + 20);
    position.setY(playerPosition.getY());
}

void Projectile::move() {
    
}