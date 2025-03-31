#include "GameLogic.hpp"
#include "characters/Player.hpp"

#include "mathutils.hpp"

GameLogic::GameLogic() {
    player = std::make_shared<Player>(Player(*this, Vector2(500, 500)));
}

void GameLogic::runTick(double ms) {
    player->move(ms);
}

double GameLogic::getScrollOffset() const {
    auto levelWidth = level->getDimensions().getX();
    auto playerPos = player->getPosition().getX();

    return mathutils::clamp(playerPos - 512, 0, levelWidth - 1024);
}