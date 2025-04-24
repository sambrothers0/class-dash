#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

#include "levels/Level.hpp"
#include "levels/LevelData.hpp"
#include "GameState.hpp"
#include "TimeKeeper.hpp"

#include <memory>

class Player;
class Enemy;

class GameLogic {
    private:
    std::shared_ptr<Player> player;
    std::shared_ptr<TimeKeeper> timer;
    

    // Current level
    std::shared_ptr<Level> level;

    int levelsCompleted = 1; // Number of levels the player has beaten, make sure to set with setLevelsCompleted to update the save file

    GameState state = GameState::INACTIVE;

    // Index of the active level
    int levelIndex = 0;

    // TODO: Replace with actual levels
    std::array<LevelData, 5> levelData;

    public:
    GameLogic();

    std::shared_ptr<Player> getPlayer(){
        return player;
    }

    std::shared_ptr<TimeKeeper> getTimer() {
        return timer;
    }
   
    std::shared_ptr<Level> getLevel() {
        return level;
    }

    int getLevelsCompleted() const {
        return levelsCompleted;
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

    bool isLevelFinished() const {
        return state == GameState::FINISHED;
    }

    void setLevel(std::shared_ptr<Level> _level) {
        level = _level;
    }

    void setLevelIndex(int index) {
        levelIndex = index;
    }

    // Setup function
    void init();

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

    // Sets the number of levels completed
    void setLevelsCompleted(int levels);

    // Saves the current number of levels completed to the file
    void saveLevelsCompleted() const;

    // Stops the current level, since the player reached the end.
    // This is separate from endLevel since that actually updates the state to inactive
    void stopLevelReachedEnd();

    // Ends the current level (completing it)
    void endLevel();
};

#endif