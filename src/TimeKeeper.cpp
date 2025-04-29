#include "TimeKeeper.hpp"
#include "SoundManager.hpp"

#include <thread>
#include <chrono>
#include <iostream>

TimeKeeper::TimeKeeper() {
    SDL_Init(SDL_INIT_TIMER);

    startTime = 60;
    timeElapsed = startTime;
    endTime = 0;
    minutes = startTime / 60;
    seconds = 0;
    timeRunning = false;
    timeElapsed = startTime;
}

void TimeKeeper::beginTimer() {
    timeRunning = true;
    warnTime = 60;
    while (timeRunning == true) {
        if (timeElapsed > 0) {
            iterations++;

            if (iterations >= 20) { // 20 = 1000 / 50
                timeElapsed -= 1;
                minutes = timeElapsed / 60;
                seconds = timeElapsed % 60;
                iterations = 0;

                // Turn off warning after player is hit
                if (abs(timeElapsed - warnTime) > 1) {
                    isWarning = false;
                }

                if (timeElapsed <= 10) { // length
                    isWarning = true;

                    // std::cout << "play sound" << std::endl;

                    if (!playedWarnSound) {
                        SoundManager::getInstance()->playSound(SoundEffect::CLOCK_TICK, true);
                        playedWarnSound = true;
                    }
                }
            }
        }
        else {
            minutes = 0;
            seconds = 0;
        }

        // More accurate timekeeping
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

/*
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (timeElapsed > 0) {
            timeElapsed -= 1;
            minutes = timeElapsed / 60;
            seconds = timeElapsed % 60;
        }
        else {
            minutes = 0;
            seconds = 0;
        }
*/
    /*
    timeElapsed = ((SDL_GetTicks64() - startTime) / 1000);
    minutes = (timeElapsed / 60);
    seconds = (timeElapsed % 60);
    */
}

void TimeKeeper::subtractTime(int _seconds) {
    timeElapsed -= _seconds;
    minutes = timeElapsed / 60;
    seconds = timeElapsed % 60;
    isWarning = true;
    warnTime = timeElapsed;
}

void TimeKeeper::resetTimer() {
    endTime = timeElapsed;
    /*
    endTime = SDL_GetTicks64();
    startTime = SDL_GetTicks64();
    */
}

std::string TimeKeeper::getTime() const {
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
