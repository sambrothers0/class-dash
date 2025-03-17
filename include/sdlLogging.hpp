#ifndef _SDL_LOGGING_H
#define _SDL_LOGGING_H

#include <string>

// Logs an SDL error
void sdlError(const std::string& message);

// Logs a TTF error
void ttfError(const std::string& message);

#endif