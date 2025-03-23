#ifndef _LEVEL_H
#define _LEVEL_H

#include "physics/Vector2.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include "sprites/Spritesheet.hpp"

// Class for the current level's data
class Level {
    private:
    Vector2 dimensions;

    // For now the level is just going to have a few blocks to be drawn (this is temporary)
    // These are relative coordinates multiplied by 32 for drawing, to make it easier to define manually
    std::vector<Vector2> blocks;
    std::vector<Spritesheet> textures;

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


    bool loadFromTMX(const std::string& filename) {
        tmx::Map map;
        if (!map.load(filename)) {
            std::cerr << "TMX failed to load: " << filename << std::endl;
            return false;
        }
    
        auto mapSize = map.getTileCount();
        auto tileSize = map.getTileSize();
        
        dimensions = Vector2(mapSize.x * tileSize.x, mapSize.y * tileSize.y);
        std::cout<<"mapsize: "<<mapSize<<" tilesize: "<<tileSize<<" dimensions: "<<dimensions.getX()<<"x"<<dimensions.getY()<<std::endl;
        
        
        //get layers, currently only one
        for (const auto& layer : map.getLayers()) {
            if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                const auto& tiles = tileLayer.getTiles();
                
                int x = 0, y = 0;
                for (const auto& tile : tiles) {
                    if (tile.ID > 0) {  
                        blocks.emplace_back(Vector2(x, y));
                    }
                    
                    x++;
                    if (x >= mapSize.x) {
                        x = 0;
                        y++;
                    }
                }
            }
        }
    
        std::cout << "Loaded Level: " << mapSize.x << "x" << mapSize.y << " tiles.\n";
        std::cout << "Loaded " << blocks.size() << " blocks from TMX.\n";
        return true;
    }
};

#endif