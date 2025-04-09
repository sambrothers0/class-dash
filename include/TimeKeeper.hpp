#ifndef _TIMEKEEPER_H
#define _TIMEKEEPER_H

#include <SDL.h>
#include <iostream>
#include <string>

class TimeKeeper {

    private:
        int minutes, seconds, startTime, endTime;
        Uint64 timeElapsed, lastTime;

    public:
        TimeKeeper(); // initialize the time 
        void resetTime(); // set reset timer by setting the startime to the current time
        void updateTime(); // updates the time in the gameloop

        std::string getTime();
    
};


#endif