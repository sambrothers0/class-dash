#include "sdlLogging.hpp"

#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"

void sdlError(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    exit(0);
}

void ttfError(const std::string& message) {
    std::cerr << message << ": " << TTF_GetError() << std::endl;
    exit(0);
}