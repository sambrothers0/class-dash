#include "GameLogic.hpp"

#include "mathutils.hpp"

#include <fstream>
#include <memory>

void GameLogic::init() {
    // Load the levels.txt file, creating it if it does not exist
    std::fstream file;

    file.open("levels.txt", std::fstream::in);

    std::string fileText;

    file >> fileText;
    file.close();

    // Try to convert from string
    try {
        int value = std::stoi(fileText);

        levelsCompleted = mathutils::clamp(value, 0, 5);
    } catch (std::invalid_argument) {
        levelsCompleted = 0;
    }
}

void GameLogic::runTick(double ms) {
    if (isLevelActive()) {
        player->move(ms);
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

void GameLogic::quitLevel() {
    state = GameState::INACTIVE;
}

void GameLogic::setLevelsCompleted(int levels) {
    levelsCompleted = levels;
    saveLevelsCompleted();
}

void GameLogic::saveLevelsCompleted() const {
    std::fstream file;

    file.open("levels.txt", std::fstream::out);

    file << std::to_string(levelsCompleted);
    file.close();
}