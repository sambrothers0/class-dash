#ifndef _LEVEL_SCREEN_H
#define _LEVEL_SCREEN_H

#include "ui/screens/Screen.hpp"

class LevelSelectScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text selectText, monday, tuesday, wednesday, thursday, friday, back;

    unsigned int levelsUnlocked = 0;

    public:
    LevelSelectScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 
        selectText(_renderer, _font, Vector2(512, 70), 50, {0, 0, 0, 255}, "Level Select"),
        monday(_renderer, _font, Vector2(512, 200), 40, {0, 0, 0, 255}, "Monday"),
        tuesday(_renderer, _font, Vector2(512, 300), 40, {0, 0, 0, 255}, "Tuesday"),
        wednesday(_renderer, _font, Vector2(512, 400), 40, {0, 0, 0, 255}, "Wednesday"),
        thursday(_renderer, _font, Vector2(512, 500), 40, {0, 0, 0, 255}, "Thursday"),
        friday(_renderer, _font, Vector2(512, 600), 40, {0, 0, 0, 255}, "Friday"),
        back(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, "Back") 

    {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~LevelSelectScreen() {}
};

#endif