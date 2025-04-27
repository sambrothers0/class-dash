#ifndef _TIMEKEEPER_H
#define _TIMEKEEPER_H

#include <SDL.h>
#include <iostream>
#include <string>

class TimeKeeper {

    private:
        int minutes, seconds, startTime, endTime;
        int timeElapsed;
        bool timeRunning;

        int iterations = 0; // This is used so that we can update the timer more frequently in case the player gets hit.

        bool isWarning = false;
        int warnTime = 60;

    public:
        TimeKeeper(); // initialize the time 
        void pauseTimer() {timeRunning = false;}
        void resetTimer(); // set reset timer by setting the startime to the current time
        void beginTimer(); // updates the time in the gameloop

         // Subtracts seconds from the timer
        void subtractTime(int _seconds);

        bool getIsWarning() const {
            return isWarning;
        }

        bool isTimeUp() const { return timeElapsed <= 0; } // check if the time is up

        std::string getTime() const;
    
};


#endif