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
    Spritesheet corgiSprite;
    Spritesheet powerupSprite;
    // std::unordered_map<uint32_t, SDL_Texture*> tilesetTextures;

    // Offset for drawing
    double scrollOffset = 0;

    // Display hitboxes?
    bool showHitboxes = false;
    bool hitboxKeyActive = false;

    // Alpha level
    double alpha = 1.0f;
    bool alphaTimerActive = false;

    Uint32 alphaTimerID;

    // Is the level complete animation done
    bool finishedLevelComplete = false;

    void drawLevel(std::shared_ptr<Level> level);

    void drawCollisionHitbox(const Vector2& position, const BoundingBox& hitbox) const;

    public:
    GameScreen(SDL_Renderer* _renderer, GameLogic& _gameLogic, TTF_Font* _font) : 
        Screen(_renderer), gameLogic(_gameLogic), font(_font), timeText(
            _renderer,
            _font,
            Vector2(150, 50),
            50,
            SDL_Color { 0, 0, 0 },
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
        ), corgiSprite(
            _renderer,
            "../assets/visual/corgi.png",
            Vector2(32, 32),
            1,
            4
        ), powerupSprite(
            _renderer,
            "../assets/visual/coffeePowerup.png",
            Vector2(32, 32),
            1,
            8
        )  {
            SoundManager::getInstance()->resumeMusic();
            SoundManager::getInstance()->playMusic(MusicTrack::LEVEL_MUSIC);
        }

    virtual void draw();

    virtual ScreenType handleEvent(SDL_Event&);
    virtual ScreenType handleExtraEvents();

    double getAlpha() const {
        return alpha;
    }

    // Decrement the alpha (transparency)
    void updateAlpha();

    ~GameScreen() {}
};

#endif