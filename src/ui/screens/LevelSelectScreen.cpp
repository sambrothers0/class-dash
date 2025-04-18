#include "ui/screens/LevelSelectScreen.hpp"
#include "mathutils.hpp"

#include "SDL2_gfxPrimitives.h"

LevelSelectScreen::LevelSelectScreen(SDL_Renderer* _renderer, TTF_Font* _font, int levelsCompleted) :
    Screen(_renderer), font(_font),
    levelSelect(_renderer, _font, Vector2(512, 70), 50, {0, 0, 0, 255}, "Level Select"),
    back(_renderer, _font, Vector2(512, 700), 30, {0, 0, 0, 255}, "Back"),
    levelsUnlocked(mathutils::clamp(levelsCompleted + 1, 1, 5)) {
    levelTexts.push_back(Text(_renderer, _font, Vector2(512, 200), 40, {0, 0, 0, 255}, "Monday"));
    levelTexts.push_back(Text(_renderer, _font, Vector2(512, 300), 40, {0, 0, 0, 255}, "Tuesday"));
    levelTexts.push_back(Text(_renderer, _font, Vector2(512, 400), 40, {0, 0, 0, 255}, "Wednesday"));
    levelTexts.push_back(Text(_renderer, _font, Vector2(512, 500), 40, {0, 0, 0, 255}, "Thursday"));
    levelTexts.push_back(Text(_renderer, _font, Vector2(512, 600), 40, {0, 0, 0, 255}, "Friday"));
}

void LevelSelectScreen::draw() {
    // Draw the level select screen
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    levelSelect.draw();

    //initialize this to something arbitrary so we dont have to call a constructor
    Text currentText = levelTexts[0];
    SDL_Color buttonColor;
    SDL_Color defaultColor = {147, 115, 64, 255}; // Default color for buttons
    SDL_Color lockedColor = {111, 94, 68, 255}; // Locked color for buttons
    SDL_Color highlightedColor = {207, 171, 112, 255}; // Highlighted color for buttons

    for (int i = 0; i < 5; i++) {
        currentText = levelTexts[i];
        if (levelsUnlocked <= i) {
            buttonColor = lockedColor;
        } else if (cursorPosition == i) {
            buttonColor = highlightedColor;
            currentText.setText(">" + levelTexts[i].getText() + "<");
        } else {
            buttonColor = defaultColor;
            currentText.setText(levelTexts[i].getText());
        }

        drawButton(512 - 225, 160 + i * 100, 450, 75, buttonColor);
        currentText.draw();
    }

    if (cursorPosition == levelsUnlocked) {
        buttonColor = highlightedColor;
        back.setText(">Back<");
    } else {
        buttonColor = defaultColor;
        back.setText("Back");
    }

    drawButton(512 - 150, 665, 300, 60, buttonColor);
    back.draw();
}

ScreenType LevelSelectScreen::handleEvent(SDL_Event& event) {
    int numOptions = levelsUnlocked + 1;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                cursorPosition = (cursorPosition - 1 + numOptions) % numOptions; // Wrap around
                break;
            case SDLK_DOWN:
                cursorPosition = (cursorPosition + 1) % numOptions; // Wrap around
                break;
            case SDLK_RETURN:
                if (cursorPosition != levelsUnlocked) {
                    return ScreenType::GAME; // this may need additional work to select correct level later
                } else {
                    return ScreenType::TITLE; // Switch to title screen
                }
            case SDLK_ESCAPE:
                return ScreenType::TITLE; // Switch to title screen
            default:
                return ScreenType::KEEP;
        }
    }
    return ScreenType::KEEP;
}