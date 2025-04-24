#include "ui/screens/LevelWinScreen.hpp"

#include "SDL2_gfxPrimitives.h"
// #include <iostream>

LevelWinScreen::LevelWinScreen(SDL_Renderer* _renderer, TTF_Font* _font, GameLogic& _gameLogic) :
    Screen(_renderer), font(_font), gameLogic(_gameLogic), 
        complete(_renderer, _font, Vector2(512, 100), 50, { 0, 0, 0, 255 }, "Level Complete!"),
        next(_renderer, _font, Vector2(512, 300), 40, { 0, 0, 0, 255 }, "Next Level"),
        quit(_renderer, _font, Vector2(512, 400), 40, { 0, 0, 0, 255 }, "Quit")
    {
        SoundManager::getInstance()->playMusic(MusicTrack::TITLE_THEME);
    }

void LevelWinScreen::draw() {
    // Draw the title screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    complete.draw();

    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    if (cursorPosition == 0) {
        buttonColor = highlightedColor;
        next.setText(">Next Level<");
    } else {
        buttonColor = defaultColor;
        next.setText("Next Level");
    }
    drawButton(512 - 250, 260, 500, 75, buttonColor);
    next.draw();

    if (cursorPosition == 1) {
        buttonColor = highlightedColor;
        quit.setText(">Quit<");
    } else {
        buttonColor = defaultColor;
        quit.setText("Quit");
    }
    drawButton(512 - 200, 360, 400, 75, buttonColor);
    quit.draw();
}

ScreenType LevelWinScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SWITCH);
                cursorPosition = (cursorPosition - 1 + 2) % 2; // Wrap around
                break;
            case SDLK_DOWN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SWITCH);
                cursorPosition = (cursorPosition + 1) % 2; // Wrap around
                break;
            case SDLK_RETURN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                if (cursorPosition == 0) {
                    // We need to set the level index too
                    gameLogic.setLevelIndex(gameLogic.getLevelIndex() + 1);

                    return ScreenType::GAME; // Resume the game
                } else if (cursorPosition == 1) {
                    return ScreenType::LEVEL_SELECT; // Quit to level select
                }
            case SDLK_ESCAPE:
                return ScreenType::LEVEL_SELECT;
            default:
                return ScreenType::KEEP;
        }
    }

    return ScreenType::KEEP;
}