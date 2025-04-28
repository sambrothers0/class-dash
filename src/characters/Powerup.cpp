#include "characters/Powerup.hpp"
#include <iostream>
void Powerup::move(double ms) {
    Character::move(ms);
}

void Powerup::animate() {
    animationTicks++;
}

BoundingBox Powerup::getHitbox() const {
    return hitbox;
}
int Powerup:: getCurrentAnimationOffset() const {
    // want coffeecup to bounce, so need to get the frame to cycle backwards, not just restart
    int totalFrames = 7; 
    int cycleTime = totalFrames * 5; 
    
    int currentTick = animationTicks % cycleTime;
    int currentFrame = currentTick / 5;
    
    if (currentFrame <= 3) {
        return currentFrame; 
    } else {
        return 6 - currentFrame; 
    }
}