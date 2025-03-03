#include "characters/Character.hpp"

void Character::move(double ms) {
    double seconds = ms / 1000;
    position += velocity * seconds;
}

Character::~Character() {}