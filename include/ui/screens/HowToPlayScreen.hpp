#ifndef _HOW_TO_PLAY_SCREEN_H
#define _HOW_TO_PLAY_SCREEN_H

#include "ui/screens/Screen.hpp"

class HowToPlayScreen : public Screen {
    private:

    TTF_Font* font;

    Text playerControlsTitle, playerControlsText1, playerControlsText2, playerControlsText3,
        playerControlsText4, objectiveTitle, objectiveText1, objectiveText2, objectiveText3,
        objectiveText4, objectiveText5, objectiveText6, objectiveText7, objectiveText8, 
        objectiveText9, objectiveText10, back;

    unsigned int levelsCompleted = 0;

    public:
    HowToPlayScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 

        // having to do a seperate one of these for each line of text
        // surely theres a better way of doing this
        playerControlsTitle(_renderer, _font, Vector2(220, 150), 25, {1, 105, 15, 255}, "Player Controls:"),
        playerControlsText1(renderer, _font, Vector2(750, 120), 20, {0, 0, 0, 255}, "Move Left: Left Arrow/A"),
        playerControlsText2(renderer, _font, Vector2(750, 150), 20, {0, 0, 0, 255}, "Move Right: Right Arrow/D"),
        playerControlsText3(renderer, _font, Vector2(750, 180), 20, {0, 0, 0, 255}, "Jump: Up Arrow/W"),
        playerControlsText4(renderer, _font, Vector2(750, 210), 20, {0, 0, 0, 255}, "Attack: SPACE"),
        objectiveTitle(_renderer, _font, Vector2(150, 400), 25, {1, 105, 15, 255}, "Objective:"),
        objectiveText1(_renderer, _font, Vector2(675, 300), 20, {0, 0, 0, 255}, "Move your character around"),
        objectiveText2(_renderer, _font, Vector2(675, 330), 20, {0, 0, 0, 255}, "the screen by going left, right,"),
        objectiveText3(_renderer, _font, Vector2(675, 360), 20, {0, 0, 0, 255}, "or jumping. Dodge obstacles"),
        objectiveText4(_renderer, _font, Vector2(675, 390), 20, {0, 0, 0, 255}, "and attack enemies by pressing"),
        objectiveText5(_renderer, _font, Vector2(675, 420), 20, {0, 0, 0, 255}, "SPACE to launch a projectile."),
        objectiveText6(_renderer, _font, Vector2(675, 450), 20, {0, 0, 0, 255}, "Reach the end of the level"),
        objectiveText7(_renderer, _font, Vector2(675, 480), 20, {0, 0, 0, 255}, "before time runs out! The"),
        objectiveText8(_renderer, _font, Vector2(675, 510), 20, {0, 0, 0, 255}, "faster you get to the end, the"),
        objectiveText9(_renderer, _font, Vector2(675, 540), 20, {0, 0, 0, 255}, "better your exam grade will be."),
        objectiveText10(_renderer, _font, Vector2(675, 570), 20, {0, 0, 0, 255}, "Press Q at any time to quit"),
        back(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, "Back") 

    {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~HowToPlayScreen() {}
};

#endif