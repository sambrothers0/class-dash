#ifndef _LEVEL_H
#define _LEVEL_H

#include "physics/Vector2.hpp"
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include "sprites/Spritesheet.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "Layer.hpp"
// Class for the current level's data
class Level {
    private:
    Vector2 dimensions;
    SDL_Renderer* renderer;
    // For now the level is just going to have a few blocks to be drawn (this is temporary)
    // These are relative coordinates multiplied by 32 for drawing, to make it easier to define manually
    std::vector<Vector2> blocks;

    std::vector<std::shared_ptr<Spritesheet>> spritesheets;
    std::vector<uint32_t> ids;
    std::vector<std::shared_ptr<Layer>> layers;

    // List of GIDs of hitboxes
    std::set<uint32_t> hitboxIDs;
    
    
    public:
    Level(Vector2 _dimensions, SDL_Renderer* _renderer) : dimensions(_dimensions), renderer(_renderer) {}

    Vector2 getDimensions() const {
        return dimensions;
    }

    std::vector<Vector2>& getBlocks() {
        return blocks;
    }

    std::vector<std::shared_ptr<Layer>>& getLayers() {
        return layers;
    }
    
    // gets global ID for a given block
    uint32_t getID(const Vector2& block) const;

    void setBlocks(std::vector<Vector2> _blocks) {
        blocks = _blocks;
    }

    // Does the list of hitbox IDs contain the given gid?
    bool isHitboxGID(uint32_t gid) const {
        return hitboxIDs.find(gid) != hitboxIDs.end();
    }

    // Returns if there is a tile at the given position with a collider
    bool colliderTileAt(const Vector2& position) const;

    // gets the correct spritesheet given a specific global ID
    std::shared_ptr<Spritesheet> getSpritesheetForGID(uint32_t gid);

    // loads map from tmx file, and populates spritesheets, blocks, and ids
    // later should be adjusted to account for layering and flip flags
    bool loadFromTMX(const std::string& filename, SDL_Renderer* renderer);

    ~Level() {}
};

#endif