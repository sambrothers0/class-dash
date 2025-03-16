#include "sdlLogging.hpp"

#include <iostream>
#include "SDL.h"

void sdlError(const std::string& message) {
    std::cerr << message << ": " << SDL_GetError() << std::endl;
    exit(0);
}