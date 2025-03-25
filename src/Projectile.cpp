#include "Projectile.hpp"

Projectile::Projectile(Vector2 playerPosition, MoveDirection playerDirection) 
    : currentDirection(playerDirection) {
    currentPosition.setX(playerPosition.getX());
    currentPosition.setY(playerPosition.getY());

    startingPosition.setX(playerPosition.getX());
    startingPosition.setY(playerPosition.getY());
}

// move the projectile along the x axis
void Projectile::move(double ms) {
    /*
    if (currentPosition.getX() < (startingPosition.getX() + 100) || (currentPosition.getX() > (startingPosition.getX() - 100))) {
        double seconds = ms/1000;
        //double moveOffset = currentPosition.getX() + velocity.getX() * seconds;
        double moveOffset = velocity.getX() * seconds;
        currentPosition.setX(currentPosition.getX() + moveOffset);   
    }
    */
   /*
   if (std::abs(currentPosition.getX() - startingPosition.getX()) > 100) {
        double seconds = ms/1000;
        //double moveOffset = currentPosition.getX() + velocity.getX() * seconds;
        double moveOffset = velocity.getX() * seconds;
        currentPosition.setX(currentPosition.getX() + moveOffset);   
    }
    else {
        setActive(false);
    }
    */
   double seconds = ms/1000;
   double moveOffset = velocity.getX() * seconds;
   currentPosition.setX(currentPosition.getX() + moveOffset);

   if (std::abs(currentPosition.getX() - startingPosition.getX()) > 500) {
        setActive(false);
   }
}

void Projectile::setVelocity(double x, double y) {
    velocity.setX(x);
    velocity.setY(y);
}