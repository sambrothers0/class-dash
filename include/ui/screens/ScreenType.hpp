#ifndef _SCREEN_TYPE_H
#define _SCREEN_TYPE_H

enum ScreenType {
    KEEP, // Represents not changing the screen type
    TITLE,
    HOW_TO_PLAY,
    LEVEL_SELECT,
    GAME,
    PAUSE,
    PAUSE_CONFIRM_QUIT,
    LEVEL_LOSE,
    LEVEL_WIN,
    GAME_FINISH
};

#endif