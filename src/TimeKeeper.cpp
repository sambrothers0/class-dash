#include "TimeKeeper.hpp"

#include <thread>
#include <chrono> 
#include <iostream>

TimeKeeper::TimeKeeper() {
    SDL_Init(SDL_INIT_TIMER);
    //startTime = 0;
    startTime = 180;
    endTime = 0;
    minutes = 0;
    seconds = 0;
    //timeElapsed = SDL_GetTicks64();
    timeElapsed = startTime;
    uint64_t lastTime = 0;
}

void TimeKeeper::updateTime() {
    //timeElapsed = ((SDL_GetTicks64() - startTime) / 1000);
    //uint64_t currentTime = SDL_GetTicks64();
    //if (((currentTime - lastTime) >= 1000) >= 0) {
        if (timeElapsed > 0) {
            timeElapsed -= 1;
            minutes = timeElapsed / 60;
            seconds = timeElapsed % 60;
        }
        else {
            minutes = 0;
            seconds = 0;
        }
        //lastTime = currentTime;
    //}

    /*
    double timeSubtract = (startTime - (SDL_GetTicks64() / 1000));
    if (timeSubtract < startTime) {     
        timeElapsed -= 1;
        minutes = ((startTime - timeElapsed) /60);
        seconds = ((startTime - timeElapsed) % 60); 
    }
    */

    //std::this_thread::sleep_for(std::chrono::seconds(1));
    /*


    timeElapsed = ((SDL_GetTicks64() - startTime) / 1000);
    minutes = (timeElapsed / 60);
    seconds = (timeElapsed % 60);
    */
}

void TimeKeeper::resetTime() {
    endTime = timeElapsed;
    /*
    endTime = SDL_GetTicks64();
    startTime = SDL_GetTicks64();
    */
} 

std::string TimeKeeper::getTime() {
    if ((minutes < 10) && (seconds < 10)) {
        return '0' + std::to_string(minutes) + ":" + "0" + std::to_string(seconds);
    }
    else if ((minutes < 10) && (seconds >= 10)) {
        return '0' + std::to_string(minutes) + ":" + std::to_string(seconds);
    }
    else if ((minutes >= 10) && (seconds < 10)) {
        return std::to_string(minutes) + ":" + "0" +std::to_string(seconds);
    }
    else {
        return std::to_string(minutes) + ":" + std::to_string(seconds);
    }
}
