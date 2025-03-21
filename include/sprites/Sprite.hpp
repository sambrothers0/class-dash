#ifndef _SPRITE_H
#define _SPRITE_H

#include "SDL.h"
#include "physics/Vector2.hpp"

class Sprite {

    private:
        SDL_Texture* sprite;
        SDL_Rect textureRect;
        SDL_Rect targetRect;
        unsigned int depth;
        

    public:
        Sprite(SDL_Texture* _sprite);

        // Position methods set position of the sprite
        // These methods can be used for setting inital position and for moving positions
        void setPosition(double x, double y);

        void setPosition(Vector2 newPosition);


        // Sets the dimensions of the sprite
        void setDimensions(double width, double height);

        // Primarily for setting the textures using a sprite map
        void setTexture(double x, double y, double width, double height);


        // Scale method scales the width and height of the sprite
        void setScale(double _scale);

        void setDepth(unsigned int newDepth);


};

#endif