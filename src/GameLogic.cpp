#include "GameLogic.hpp"

void GameLogic::runTick(double ms) {
    player.move(ms);
}