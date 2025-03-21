#ifndef _SPRITESHEET_H
#define _SPRITESHEET_H

#include "SDL.h"
#include "SDL_image.h"

#include "physics/Vector2.hpp"

// Spritesheet lets you load a single file to use it as a spritesheet
class Spritesheet {
    private:
    SDL_Renderer* renderer;
    
    std::string path;

    SDL_Texture* texture = nullptr;

    // Dimensions of a single sprite
    Vector2 spriteSize;

    // Dimensions of the spritesheet
    int rows;
    int columns;

    public:
    Spritesheet(SDL_Renderer* _renderer, std::string path, Vector2 _spriteSize, int _rows, int _columns);

    // Draws the given texture at the given index
    void draw(int index, Vector2 position);

    ~Spritesheet();
};

#endif