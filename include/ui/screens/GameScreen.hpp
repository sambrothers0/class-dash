#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "characters/Player.hpp"
#include "ui/screens/Screen.hpp"

#include "sprites/Spritesheet.hpp"

class GameScreen : public Screen {
    private:
    GameLogic& gameLogic;
    TTF_Font* font;

    // Spritesheet for the player
    Spritesheet playerSprite;
    // std::unordered_map<uint32_t, SDL_Texture*> tilesetTextures;

    // Offset for drawing
    double scrollOffset;

    void drawLevel(std::shared_ptr<Level> level);

    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic, TTF_Font* _font) :
        Screen(_renderer), gameLogic(_gameLogic), font(_font), playerSprite(
            _renderer,
            "../assets/visual/player-spritesheet.png",
            Vector2(PLAYER_WIDTH, PLAYER_HEIGHT),
            5,
            2
        ) {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event&);
    void updateLevelTextures(std::shared_ptr<Level> level);


    ~GameScreen() {}
};

#endif