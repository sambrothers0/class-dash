#include "GameLogic.hpp"

#include "mathutils.hpp"

#include <memory>

void GameLogic::runTick(double ms) {
    if (isLevelActive()) {
        player->move(ms);
        timer->updateTime();
    }
}

double GameLogic::getScrollOffset() const {
    auto levelWidth = level->getDimensions().getX();
    auto playerPos = player->getPosition().getX();

    return mathutils::clamp(playerPos - 512, 0, levelWidth - 1024);
}

void GameLogic::activate(SDL_Renderer* renderer) {
    level = std::make_shared<Level>(Vector2(2240, 768), renderer);
    if (!level->loadFromTMX("../assets/visual/Level2.tmx", renderer)) {
        std::cerr << "Failed to load level!" << std::endl;
        return;
    }

    player = std::make_shared<Player>(Vector2(500, 500));

    state = GameState::ACTIVE;
}

void GameLogic::pause() {
    player->stopMoving();
    state = GameState::PAUSED;
}

void GameLogic::resume() {
    state = GameState::ACTIVE;
}