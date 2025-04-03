#ifndef _GAME_STATE_H
#define _GAME_STATE_H

// Represents the current state of GameState
enum GameState {
    INACTIVE, // No level loaded
    ACTIVE, // In game
    PAUSED // Pause menu
};

#endif