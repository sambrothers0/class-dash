#include "characters/Character.hpp"
#include "physics/physicsConstants.hpp"

void Character::move(double ms) {
    double seconds = ms / 1000;

    velocity.setY(velocity.getY() + GRAVITY * seconds) ;

    position += velocity * seconds;
}



Character::~Character() {}