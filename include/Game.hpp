#ifndef _GAME_H
#define _GAME_H

#include "GameLogic.hpp"
#include "PlayerView.hpp"

// Main Game class
class Game {
    private:
    GameLogic gameLogic;
    PlayerView playerView;

    public:
    Game() : gameLogic(), playerView(*this) {}

    GameLogic& getGameLogic() {
        return gameLogic;
    }

    void run();
};

#endif