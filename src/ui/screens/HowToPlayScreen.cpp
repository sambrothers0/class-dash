#include "ui/screens/HowToPlayScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void HowToPlayScreen::draw() {
    boxRGBA(renderer, 0, 0, 1024, 768, 255, 255, 255, 255); //placeholder

    howToPlay.draw();
    playerControlsTitle.draw();
    playerControlsText1.draw();
    playerControlsText2.draw();
    playerControlsText3.draw();
    playerControlsText4.draw();
    objectiveTitle.draw();
    objectiveText1.draw();
    objectiveText2.draw();
    objectiveText3.draw();
    objectiveText4.draw();
    objectiveText5.draw();
    objectiveText6.draw();
    objectiveText7.draw();
    objectiveText8.draw();
    objectiveText9.draw();
    objectiveText10.draw();

    drawButton(512 - 250, 665, 500, 60, {207, 171, 112, 255});
    back.draw();
}

ScreenType HowToPlayScreen::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::TITLE; // Switch to title screen
            case SDLK_ESCAPE:
                SoundManager::getInstance()->playSound(SoundEffect::BUTTON_SELECT);
                return ScreenType::TITLE; // Switch to title screen
            default:
                return ScreenType::KEEP;
        }
    }
    return ScreenType::KEEP;
}