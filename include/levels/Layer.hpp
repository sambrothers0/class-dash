#ifndef _LAYER_H
#define _LAYER_H

#include "physics/Vector2.hpp"
#include <vector>
#include <iostream>
#include "SDL.h"

class Layer {
    private:
    std::vector<Vector2> blocks;
    std::vector<uint32_t> ids;

    public:
    Layer(std::vector<Vector2> _blocks, std::vector<uint32_t> _ids) : blocks(_blocks), ids(_ids) {}

    const std::vector<Vector2>& getBlocks() const {
        return blocks;
    }

    // gets global ID for a given block
    uint32_t getID(const Vector2& block) const;
};

#endif