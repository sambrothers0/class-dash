#ifndef _PAUSE_CONFIRM_QUIT_SCREEN_H
#define _PAUSE_CONFIRM_QUIT_SCREEN_H

#include "ui/screens/Screen.hpp"

// This screen handles confirming if the player wants to quit
class PauseConfirmQuitScreen : public Screen {
    private:

    TTF_Font* font;

    Text confirmText;

    public:
    PauseConfirmQuitScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), confirmText(
            _renderer,
            _font,
            Vector2(512, 650),
            35,
            SDL_Color { 0, 0, 0 },
            "Do you really want to quit? Press Enter to confirm, Esc to cancel"
        )  {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~PauseConfirmQuitScreen() {}
};

#endif