#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "characters/Player.hpp"
#include "ui/screens/Screen.hpp"

#include "sprites/Spritesheet.hpp"

#include "physics/BoundingBox.hpp"

class GameScreen : public Screen {
    private:
    GameLogic& gameLogic;
    TTF_Font* font;

    Text timeText;

    // Spritesheet for the player
    Spritesheet playerSprite;
    Spritesheet playerProjectileSprite;
    Spritesheet enemySprite;
    // std::unordered_map<uint32_t, SDL_Texture*> tilesetTextures;

    // Offset for drawing
    double scrollOffset;

    // Display hitboxes?
    bool showHitboxes = false;
    bool hitboxKeyActive = false;

    void drawLevel(std::shared_ptr<Level> level);

    void drawCollisionHitbox(const Vector2& position, const BoundingBox& hitbox) const;

    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic, TTF_Font* _font) : 
        Screen(_renderer), gameLogic(_gameLogic), font(_font), timeText(
            _renderer,
            _font,
            Vector2(150, 100),
            50,
            SDL_Color { 255, 255, 255 },
            //"Test"
            gameLogic.getTimer()->getTime()
        ), playerSprite(
            _renderer,
            "../assets/visual/player-spritesheet.png",
            Vector2(PLAYER_WIDTH, PLAYER_HEIGHT),
            5,
            2
        ), playerProjectileSprite(
            _renderer,
            "../assets/visual/objectSpritesheet.png",
            Vector2(32, 32),
            1,
            4
        ), enemySprite(
            _renderer, 
            "../assets/visual/regularEnemysSpritesheet.png",
            Vector2(ENEMY_WIDTH, ENEMY_HEIGHT),
            4,
            1
        ) {}

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event&);
    virtual ScreenType handleExtraEvents();

    void updateLevelTextures(std::shared_ptr<Level> level);


    ~GameScreen() {}
};

#endif