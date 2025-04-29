#ifndef _LEVEL_DATA_H
#define _LEVEL_DATA_H

#include <string>
#include "levels/EnemyData.hpp"

// The LevelData class contains the names of levels + data that can't easily be encoded in Tiled, such as enemy locations.
class LevelData {
    private:
    std::string filePath;

    std::vector<EnemyData> enemies;

    public:
    LevelData() : filePath("") {}

    LevelData(std::string _filePath) : filePath(_filePath) {}

    const std::string& getFilePath() const {
        return filePath;
    }

    const std::vector<EnemyData>& getEnemies() const {
        return enemies;
    }
};

#endif