#ifndef _TIMEKEEPER_H
#define _TIMEKEEPER_H

#include <SDL.h>
#include <iostream>
#include <string>

class TimeKeeper {

    private:
        int minutes, seconds, startTime;
        Uint64 timeElapsed;
        bool reset = false;

    public:
        TimeKeeper(); // initialize the time 
        //void startTimer(); // sets startTime to current time when time resets
        void resetTimer(); // set reset timer by setting the startime to the current time
        void updateTime(); // updates the time in the gameloop

        std::string getTime();
        
        int getMinutes() {return minutes;}
        int getSeconds() {return seconds;}
    
};


#endif