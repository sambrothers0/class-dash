#ifndef _TIMEKEEPER_H
#define _TIMEKEEPER_H

#include <SDL.h>
#include <iostream>
#include <string>

class TimeKeeper {

    private:
        int minutes, seconds, startTime, endTime;
        Uint64 timeElapsed;
        bool timeRunning;

    public:
        TimeKeeper(); // initialize the time 
        void pauseTimer() {timeRunning = false;}
        void resetTimer(); // set reset timer by setting the startime to the current time
        void beginTimer(); // updates the time in the gameloop
        bool isTimeUp() { return timeElapsed <= 0; } // check if the time is up

        std::string getTime();
    
};


#endif