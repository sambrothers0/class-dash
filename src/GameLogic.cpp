#include "GameLogic.hpp"
#include "characters/Player.hpp"

#include "mathutils.hpp"

#include <fstream>
#include <memory>
#include <thread>
#include <chrono>

GameLogic::GameLogic() {
    std::vector<EnemyData> level1Enemies {
        EnemyData(Vector2(900, 580), 600, 1200)
    };

    levelData[0] = LevelData("../assets/visual/SunkenGardenLevel.tmx", level1Enemies);
    levelData[1] = LevelData("../assets/visual/Level1.tmx");
    levelData[2] = LevelData("../assets/visual/Level2.tmx");

    std::vector<EnemyData> level4Enemies {
        EnemyData(Vector2(608, 480), 608, 736),
        EnemyData(Vector2(1420, 400), 1410, 1756)
    };

    levelData[3] = LevelData("../assets/visual/Level3.tmx", level4Enemies);

    levelData[4] = LevelData("../assets/visual/ColliderTest.tmx");
}

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

        for (auto enemy : level->getEnemies()) {
            enemy->moveOnTrack(ms);
        }
    }
}

double GameLogic::getScrollOffset() const {
    auto levelWidth = level->getDimensions().getX();
    auto playerPos = player->getPosition().getX();

    return mathutils::clamp(playerPos - 512, 0, levelWidth - 1024);
}

void GameLogic::activate(SDL_Renderer* renderer) {
    level = std::make_shared<Level>(Vector2(2240, 768)); // In the future this maybe should not be hardcoded
    timer = std::make_shared<TimeKeeper>();
    std::thread time(&TimeKeeper::beginTimer, timer);
    time.detach();

    if (!level->loadData(levelData.at(levelIndex), renderer)) {
        std::cerr << "Failed to load level!" << std::endl;
        return;
    }

    auto spawn = level-> getPlayerSpawnPoint();
    std::cout<<spawn.getX()<<" "<<spawn.getY()<<std::endl;

    // player = std::make_shared<Player>(Player(*this, Vector2(500, 500)));
    player = std::make_shared<Player>(Player(*this, spawn));

    state = GameState::ACTIVE;
}

void GameLogic::pause() {
    player->stopMoving();
    state = GameState::PAUSED;
    timer->pauseTimer();
}

void GameLogic::resume() {
    state = GameState::ACTIVE;
    std::thread time(&TimeKeeper::beginTimer, timer);
    time.detach();
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