#include "characters/Character.hpp"

const float GRAVITY = 980.0f; 

void Character::move(double ms) {
    double seconds = ms / 1000;

    velocity.setY(velocity.getY() + GRAVITY *  seconds) ;

    position += velocity * seconds;
}



Character::~Character() {}