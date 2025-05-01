#ifndef _ENEMY_DATA_H
#define _ENEMY_DATA_H

#include "physics/Vector2.hpp"

// This represents the data for an enemy to be put in the level.
class EnemyData {
    private:
    Vector2 startPos;

    double trackStart, trackEnd;
    bool canShoot;
    bool isBiker;

    public:
    EnemyData(Vector2 _startPos, double _trackStart, double _trackEnd, bool _canShoot, bool _isBiker) : startPos(_startPos), trackStart(_trackStart), trackEnd(_trackEnd), canShoot(_canShoot), isBiker(_isBiker) {}

    const Vector2& getStartPos() const {
        return startPos;
    }

    double getTrackStart() const {
        return trackStart;
    }

    double getTrackEnd() const {
        return trackEnd;
    }

    bool getCanShoot() const {
        return canShoot;
    }
    bool getIsBiker() const {
        return isBiker;
    }
};

#endif