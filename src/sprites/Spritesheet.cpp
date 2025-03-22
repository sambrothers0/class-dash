#include "sprites/Spritesheet.hpp"

#include "sdlLogging.hpp"

#include <iostream>

// Helper function to load a texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == NULL)
        sdlError("Could not load texture!");

    return texture;
}

Spritesheet::Spritesheet(SDL_Renderer* _renderer, std::string _path, Vector2 _spriteSize, int _rows, int _columns) : renderer(_renderer), path(_path), spriteSize(_spriteSize), rows(_rows), columns(_columns) {}

void Spritesheet::draw(int index, Vector2 position, bool flipped) {
    if (texture == nullptr) {
        texture = loadTexture(renderer, path);
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

    SDL_RenderCopyEx(renderer, texture, &sourcePosition, &drawPosition, 0, NULL, flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Spritesheet::draw(int index, Vector2 position) {
    draw(index, position, false);
}

Spritesheet::~Spritesheet() {
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
}