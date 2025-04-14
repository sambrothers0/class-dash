#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text levelSelect, back;

    unsigned int levelsUnlocked;

    // List of level texts (this exists to make drawing them easier)
    std::vector<Text> levelTexts;

    public:
    LevelSelectScreen(SDL_Renderer* _renderer, TTF_Font* _font, int levelsCompleted);

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~LevelSelectScreen() {}
};

#endif