#ifndef _SPRITE_H
#define _SPRITE_H

#include "SDL.h"
#include "Vector2.hpp"

class Sprite {

    private:
        SDL_Texture* sprite;
        SDL_Rect textureRect;
        SDL_Rect targetRect;
        Vector2 position;
        double scale;

    public:
        Sprite(SDL_Texture* _sprite);

        // Position methods set position of the sprite
        void setPosition(double x, double y);

        void setPosition(Vector2 newPosition);

        void movePositon();

        // Sets the dimentions of the sprite
        void setDimensions(double x, double y);


        // Scale methods scale the width and height of the sprite
        void setScale(double newScale);

        void scale(double _scale);

        void setAngle();

        void rotate();


};

#endif