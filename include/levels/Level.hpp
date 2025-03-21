#ifndef _LEVEL_H
#define _LEVEL_H

#include "physics/Vector2.hpp"
#include <vector>

// Class for the current level's data
class Level {
    private:
    Vector2 dimensions;

    // For now the level is just going to have a few blocks to be drawn (this is temporary)
    // These are relative coordinates multiplied by 32 for drawing, to make it easier to define manually
    std::vector<Vector2> blocks;

    public:
    Level(Vector2 _dimensions) : dimensions(_dimensions) {}

    Vector2 getDimensions() const {
        return dimensions;
    }

    std::vector<Vector2>& getBlocks() {
        return blocks;
    }

    void setBlocks(std::vector<Vector2> _blocks) {
        blocks = _blocks;
    }
};

#endif