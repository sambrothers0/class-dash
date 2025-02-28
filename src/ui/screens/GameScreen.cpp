#include "ui/screens/GameScreen.hpp"

#include "SDL2_gfxPrimitives.h"

void GameScreen::draw() {
    // Draw a box for now
    boxRGBA(renderer, 50, 50, 250, 250, 0, 255, 255, 255);
}