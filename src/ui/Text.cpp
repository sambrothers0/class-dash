#include "ui/Text.hpp"

#include "sdlLogging.hpp"

void Text::generateTexture() {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    if (textSurface == NULL)
        ttfError("Could not create text surface!");

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface); // This line seems to cause the

    if (texture == NULL)
        sdlError("Could not create texture!");

    SDL_FreeSurface(textSurface);

    generatedTexture = texture;

    // Calculate the size of the rendered text (this seems to work)
    int w, h;

    TTF_SizeText(font, text.c_str(), &w, &h);

    double ratio = (double) fontSize / h;
    double width = (double) w * ratio;
    double height = (double) h * ratio;

    renderedSize = Vector2(width, height);
}

void Text::draw() {
    if (generatedTexture == nullptr) {
        generateTexture();
    }

    double width = renderedSize.getX();
    double height = renderedSize.getY();

    SDL_Rect location = {(int) (position.getX() - width / 2), (int) (position.getY() - height / 2), (int) width, (int) height};

    SDL_RenderCopy(renderer, generatedTexture, NULL, &location);
}

void Text::setText(const std::string& _text) {
    // Only re-generate the texture if it is different
    if (text != _text) {
        text = _text;
        generateTexture();
    }
}

Text::~Text() {
    if (generatedTexture != nullptr)
        SDL_DestroyTexture(generatedTexture);
}