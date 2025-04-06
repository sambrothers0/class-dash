#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "characters/Player.hpp"
#include "levels/Level.hpp"
#include "GameState.hpp"

#include <memory>

class GameLogic {
    private:
    std::shared_ptr<Player> player;

    // Current level
    std::shared_ptr<Level> level;

    int levelsUnlocked = 0;

    GameState state = GameState::INACTIVE;

    public:
    GameLogic(){}

    std::shared_ptr<Player> getPlayer(){
        return player;
    }

    std::shared_ptr<Level> getLevel() {
        return level;
    }

    int getLevelsUnlocked() const {
        return levelsUnlocked;
    }

    bool isNoLevelActive() const {
        return state == GameState::INACTIVE;
    }

    bool isLevelActive() const {
        return state == GameState::ACTIVE;
    }

    bool isLevelPaused() const {
        return state == GameState::PAUSED;
    }

    void setLevel(std::shared_ptr<Level> _level) {
        level = _level;
    }

    // Runs a game tick lasting this many milliseconds
    void runTick(double ms);

    // Gets the current horizontal offset for the camera for scrolling
    double getScrollOffset() const;

    // Sets up the game to be active
    void activate(SDL_Renderer* renderer);

    // Pauses the game
    void pause();

    // Resumes the game
    void resume();

    // Quits out of a level
    void quitLevel();
};

#endif