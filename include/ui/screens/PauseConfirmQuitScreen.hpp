#ifndef _PAUSE_CONFIRM_QUIT_SCREEN_H
#define _PAUSE_CONFIRM_QUIT_SCREEN_H

#include "ui/screens/Screen.hpp"

// This screen handles confirming if the player wants to quit
class PauseConfirmQuitScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text confirm, yes, no;

    std::string backgroundPath = "../assets/visual/crim-dell.png";

    public:
    PauseConfirmQuitScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 
            confirm(_renderer, _font, Vector2(512, 100), 30, { 0, 0, 0, 255 }, "Do you really want to quit?"),
            yes(_renderer, _font, Vector2(512, 300), 40, { 0, 0, 0, 255 }, "Yes"),
            no(_renderer, _font, Vector2(512, 400), 40, { 0, 0, 0, 255 }, "No")
        {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~PauseConfirmQuitScreen() {}
};

#endif