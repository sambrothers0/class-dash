#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "levels/Level.hpp"

#include <memory>

class Player;

class GameLogic {
    private:
    std::shared_ptr<Player> player;

    // Current level
    std::shared_ptr<Level> level;

    public:
    GameLogic();

    std::shared_ptr<Player> getPlayer() {
        return player;
    }

    std::shared_ptr<Level> getLevel() {
        return level;
    }

    void setLevel(std::shared_ptr<Level> _level) {
        level = _level;
    }

    // Runs a game tick lasting this many milliseconds
    void runTick(double ms);

    // Gets the current horizontal offset for the camera for scrolling
    double getScrollOffset() const;
};

#endif