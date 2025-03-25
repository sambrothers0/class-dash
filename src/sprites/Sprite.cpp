#include "sprites/Sprite.hpp"

Sprite::Sprite(SDL_Texture* _sprite, SDL_Renderer* _renderer) : sprite(_sprite), renderer(_renderer) {
    targetRect.x = 0;
    targetRect.y = 0;
    textureRect.x = 0;
    textureRect.y = 0;
    SDL_QueryTexture(sprite, NULL, NULL, &textureRect.w, &textureRect.h);
}

void Sprite::setPosition(double x, double y) {
    targetRect.x = x;
    targetRect.y = y;
}

// Can be used for setting inital position or for sprite movement
void Sprite::setPosition(Vector2 newPosition) {
    targetRect.x = newPosition.getX();
    targetRect.y = newPosition.getY();
}

// Sets the dimensions of the sprite
void Sprite::setDimensions(double width, double height) {
    targetRect.w = width;
    targetRect.h = height;
}

void Sprite::setTexture(double x, double y, double width, double height) {
    textureRect.x = x;
    textureRect.y = y;
    textureRect.w = width;
    textureRect.h = height;
}

// Scale method scale the width and height of the sprite with the texture
// keeps the size of the target proportional to the texture
void Sprite::setScale(double _scale) {
    targetRect.w = textureRect.w * _scale;
    targetRect.h = textureRect.h * _scale;
}

// depth tells when a sprite should be drawn in comparison to others
void Sprite::setDepth(unsigned int newDepth) {
    depth = newDepth;
}

// draws the sprite to the screen
void Sprite::draw() {
    SDL_RenderCopy(renderer, sprite, &textureRect, &targetRect);
}