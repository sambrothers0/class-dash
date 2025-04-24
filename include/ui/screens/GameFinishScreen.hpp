#ifndef _GAME_FINISH_SCREEN_H
#define _GAME_FINISH_SCREEN_H

#include "ui/screens/Screen.hpp"

class GameFinishScreen : public Screen {
    private:

    TTF_Font* font;

    int cursorPosition = 0;

    Text title, subtitle1, subtitle2, quit;

    SDL_Texture* background = nullptr;

    public:
    GameFinishScreen(SDL_Renderer* _renderer, TTF_Font* _font) :
    Screen(_renderer), font(_font), 
        title(_renderer, _font, Vector2(512, 100), 50, { 0, 0, 0, 255 }, "Congratulations!"),
        subtitle1(_renderer, _font, Vector2(512, 200), 40, { 0, 0, 0, 255 }, "You got every final on"),
        subtitle2(_renderer, _font, Vector2(512, 300), 40, { 0, 0, 0, 255 }, "time and graduated!"),
        quit(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, ">Quit<")
    {
        SoundManager::getInstance()->playMusic(MusicTrack::TITLE_THEME);
    }

    virtual void draw();

    void drawBackground();

    virtual ScreenType handleEvent(SDL_Event& event);

    ~GameFinishScreen() {};
};

#endif