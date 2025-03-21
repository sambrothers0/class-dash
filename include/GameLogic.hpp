#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "characters/Player.hpp"
#include "levels/Level.hpp"

#include <memory>

class GameLogic {
    private:
    Player player;

    // Current level
    std::shared_ptr<Level> level;

    public:
    GameLogic() : player(Vector2(500, 500)) {}

    Player& getPlayer() {
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