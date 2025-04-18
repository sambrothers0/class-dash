#ifndef _LAYER_H
#define _LAYER_H

#include "physics/Vector2.hpp"
#include <vector>
#include <iostream>
#include "SDL.h"
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tuple>

class Layer {
    private:
    std::vector<std::tuple<Vector2, int>> blocks;
    std::vector<uint32_t> ids;
    std::vector<tmx::TileLayer::Tile> layerTiles;
    std::string name;
    float opacity;


    public:
    Layer(std::vector<std::tuple<Vector2, int>> _blocks, std::vector<uint32_t> _ids, std::string _name, float _opacity) : blocks(_blocks), ids(_ids), name(_name), opacity(_opacity){}

    const std::vector<std::tuple<Vector2, int>>& getBlocks() const {
        return blocks;
    }

    // gets global ID for a given block (probably don't use this)
    uint32_t getID(const Vector2& block) const;

    // Gets the global ID at a given index
    uint32_t getID(int index) const;

    bool hasFlipFlag(int index) const ;
    float getOpacity() const{
        return opacity;
    }
};

#endif