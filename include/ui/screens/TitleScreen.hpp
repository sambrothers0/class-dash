#ifndef _TITLE_SCREEN_H
#define _TITLE_SCREEN_H

#include "ui/screens/Screen.hpp"
#include <iostream>
    
class TitleScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text title, start, howToPlay;

    SDL_Texture* background = nullptr;

    public:
    TitleScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
        Screen(_renderer), font(_font), 
        title(_renderer, _font, Vector2(512, 130), 50, {0, 0, 0, 255}, "Class Dash"),
        start(_renderer, _font, Vector2(512, 585), 40, {0, 0, 0, 255}, "Start"),
        howToPlay(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, "How to Play")
    {
        SoundManager::getInstance()->playMusic(MusicTrack::TITLE_THEME);
    }

    virtual void draw();

    void drawBackground(SDL_Renderer* renderer, SDL_Texture* texture);

    virtual ScreenType handleEvent(SDL_Event& event);

    ~TitleScreen();
};

#endif