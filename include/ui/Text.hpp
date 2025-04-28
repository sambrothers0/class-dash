#ifndef _TEXT_H
#define _TEXT_H

#include "SDL.h"
#include "SDL_ttf.h"

#include "physics/Vector2.hpp"
#include <string>

// Text element centered around the position
class Text {
    private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    Vector2 position;
    double fontSize;
    SDL_Color color;

    std::string text;

    SDL_Texture* generatedTexture = nullptr;

    // Size of the rendered text
    Vector2 renderedSize;

    // Generates the texture
    void generateTexture();

    public:
    Text(SDL_Renderer* _renderer, TTF_Font* _font, const Vector2& _position, double _fontSize, SDL_Color _color, std::string _text) :
        renderer(_renderer), font(_font), position(_position), fontSize(_fontSize), color(_color), text(_text) {}

    void draw();

    void setText(const std::string& _text);
    const std::string& getText() const { return text; }

    void setColor(SDL_Color _color);

    ~Text();
};

#endif