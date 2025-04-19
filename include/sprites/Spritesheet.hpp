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

    // Has the texture been loaded
    bool hasLoadedTexture = false;

    // Dimensions of a single sprite
    Vector2 spriteSize;

    uint32_t firstGID=0, lastGID=0;

    // Dimensions of the spritesheet
    int rows;
    int columns;

    void loadTexture();

    public:
    Spritesheet(SDL_Renderer* _renderer, std::string path, Vector2 _spriteSize, int _rows, int _columns);

    void setGID(uint32_t first, uint32_t last) {
        firstGID=first;
        lastGID=last;
    }
    
    uint32_t getFirstGID(){
        return firstGID;
    }

    bool containsID(uint32_t index) const;

    // Draws the given texture at the given index
    void draw(int index, Vector2 position, bool flipped, float opacity);

    void draw(int index, Vector2 position);

    ~Spritesheet();
};

#endif