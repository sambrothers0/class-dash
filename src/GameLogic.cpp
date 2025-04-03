#include "GameLogic.hpp"

#include "mathutils.hpp"

void GameLogic::runTick(double ms) {
    player.move(ms);
    timer.updateTime();
}

double GameLogic::getScrollOffset() const {
    auto levelWidth = level->getDimensions().getX();
    auto playerPos = player.getPosition().getX();

    return mathutils::clamp(playerPos - 512, 0, levelWidth - 1024);
}