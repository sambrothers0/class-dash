#include "sprites/Spritesheet.hpp"

#include "sdlLogging.hpp"

#include <iostream>
#include <cassert>

// This causes the segfault but idk why, it shouldn't even be called
void Spritesheet::loadTexture() {
    texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == NULL) {
        sdlError("Could not load texture!");
    } else {
        hasLoadedTexture = true;
    }
}

Spritesheet::Spritesheet(SDL_Renderer* _renderer, std::string _path, Vector2 _spriteSize, int _rows, int _columns) : renderer(_renderer), path(_path), spriteSize(_spriteSize), rows(_rows), columns(_columns) {}

void Spritesheet::draw(int index, Vector2 position, bool flipped, float opacity) {
    if (!hasLoadedTexture) {
        loadTexture();
    }

    int row = index / columns;
    int column = index % columns;

    auto sourcePosition = SDL_Rect {
        (int) (column * spriteSize.getX()),
        (int) (row * spriteSize.getY()),
        (int) spriteSize.getX(),
        (int) spriteSize.getY()
    };

    auto drawPosition = SDL_Rect {
        (int) (position.getX() - spriteSize.getX() / 2),
        (int) (position.getY() - spriteSize.getY() / 2),
        (int) spriteSize.getX(),
        (int) spriteSize.getY()
    };
    SDL_SetTextureAlphaMod(texture, opacity*255);
    SDL_RenderCopyEx(renderer, texture, &sourcePosition, &drawPosition, 0, NULL, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Spritesheet::draw(int index, Vector2 position) {
    draw(index, position, false, 1.0);
}

bool Spritesheet::containsID(uint32_t index) const {
    if(index>=firstGID && index<=lastGID){
        return true;
    } return false;
}

Spritesheet::~Spritesheet() {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
}