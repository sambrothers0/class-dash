#include "GameLogic.hpp"

#include "mathutils.hpp"

void GameLogic::runTick(double ms) {
    player.move(ms);
    
    //if (player.getProjectile().isActive()) {
    if (player.projectile.isActive()) {
        player.projectile.move(ms);
    }
        //player.getProjectile().move(ms);
    //}
}

double GameLogic::getScrollOffset() const {
    auto levelWidth = level->getDimensions().getX();
    auto playerPos = player.getPosition().getX();

    return mathutils::clamp(playerPos - 512, 0, levelWidth - 1024);
}