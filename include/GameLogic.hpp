#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "characters/Player.hpp"

class GameLogic {
    private:
    Player player;

    public:
    GameLogic() : player(Vector2(500, 500)) {}

    Player& getPlayer() {
        return player;
    }

    // Runs a game tick lasting this many milliseconds
    void runTick(double ms);
};

#endif