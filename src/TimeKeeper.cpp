#include "TimeKeeper.hpp"

#include <iostream>

TimeKeeper::TimeKeeper() {
    SDL_Init(SDL_INIT_TIMER);
    startTime = 0;
    endTime = 0;
    minutes = 0;
    seconds = 0;
    timeElapsed = SDL_GetTicks64();
}

void TimeKeeper::updateTime() {
    timeElapsed = ((SDL_GetTicks64() - startTime) / 1000);
    minutes = (timeElapsed / 60);
    seconds = (timeElapsed % 60);

    std::cout << "Testing" << std::endl;
    std::cout << minutes << ":" << seconds << std::endl;
}

void TimeKeeper::resetTime() {
    endTime = SDL_GetTicks64();
    startTime = SDL_GetTicks64();
} 

std::string TimeKeeper::getTime() {
    if ((minutes < 10) & (seconds < 10)) {
        return '0' + std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
    }
    else if ((minutes < 10) & (seconds >= 10)) {
        return '0' + std::to_string(minutes) + ":" + std::to_string(seconds);
    }
    else if ((minutes >= 10) & (seconds < 10)) {
        return std::to_string(minutes) + ":" + "0" +std::to_string(seconds);
    }
    else {
        return std::to_string(minutes) + ":" + std::to_string(seconds);
    }
}
