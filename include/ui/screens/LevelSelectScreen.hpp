#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    private:
    GameLogic& gameLogic;

    TTF_Font* font;

    int cursorPosition = 0;

    Text levelSelect, back;

    unsigned int levelsUnlocked = 0;

    // List of level texts (this exists to make drawing them easier)
    std::vector<Text> levelTexts;

    // Runs when a level is selected (index goes from 0 to 4)
    void onLevelSelected(int level);

    public:
    LevelSelectScreen(GameLogic& _gameLogic, SDL_Renderer* _renderer, TTF_Font* _font, int levelsCompleted);

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~LevelSelectScreen() {}
};

#endif