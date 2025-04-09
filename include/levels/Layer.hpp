#ifndef _LAYER_H
#define _LAYER_H

#include "physics/Vector2.hpp"
#include <vector>
#include <iostream>
#include "SDL.h"
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

class Layer {
    private:
    std::vector<Vector2> blocks;
    std::vector<uint32_t> ids;
    std::vector<tmx::TileLayer::Tile> layerTiles;
    std::string name;



    public:
    Layer(std::vector<Vector2> _blocks, std::vector<uint32_t> _ids, std::string _name) : blocks(_blocks), ids(_ids), name(_name){}

    const std::vector<Vector2>& getBlocks() const {
        return blocks;
    }

    // gets global ID for a given block
    uint32_t getID(const Vector2& block) const;

    bool hasFlipFlag(const Vector2& block) const ;
};

#endif