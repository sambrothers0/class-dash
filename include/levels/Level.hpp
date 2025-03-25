#ifndef _LEVEL_H
#define _LEVEL_H

#include "physics/Vector2.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include "sprites/Spritesheet.hpp"
#include "SDL.h"
#include "SDL_image.h"
// Class for the current level's data
class Level {
    private:
    Vector2 dimensions;
    SDL_Renderer* renderer;
    // For now the level is just going to have a few blocks to be drawn (this is temporary)
    // These are relative coordinates multiplied by 32 for drawing, to make it easier to define manually
    std::vector<Vector2> blocks;
    std::vector<tmx::Tileset> tilesets;
    std::vector<std::shared_ptr<Spritesheet>> spritesheets;
    std::vector<uint32_t> ids;
    
    public:
    Level(Vector2 _dimensions, SDL_Renderer* _renderer) : dimensions(_dimensions), renderer(_renderer){}

    Vector2 getDimensions() const {
        return dimensions;
    }

    std::vector<Vector2>& getBlocks() {
        return blocks;
    }

    
    // gets global ID for a given block
    uint32_t getID(const Vector2& block) const { 
        for (size_t i = 0; i < blocks.size(); ++i) {
            if (blocks[i] == block) { 
                return ids[i];         
            }
        }
        return 0;  
    }

    void setBlocks(std::vector<Vector2> _blocks) {
        blocks = _blocks;
    }

    // gets the correct spritesheet given a specific global ID
    std::shared_ptr<Spritesheet> getSpritesheetForGID(uint32_t gid) {
        for (const auto& spritesheet : spritesheets) {
            if (spritesheet->containsID(gid)) {
                return spritesheet;
            }
        }
        return nullptr; // No matching spritesheet found
    }

    // loads map from tmx file, and populates spritesheets, blocks, and ids
    // later should be adjusted to account for layering and flip flags
    bool loadFromTMX(const std::string& filename, SDL_Renderer* renderer) {
        tmx::Map map;
        if (!map.load(filename)) {
            std::cerr << "TMX failed to load: " << filename << std::endl;
            return false;
        }
    
        auto mapSize = map.getTileCount();
        auto tileSize = map.getTileSize();
        
        dimensions = Vector2(mapSize.x * tileSize.x, mapSize.y * tileSize.y);
        std::cout<<"mapsize: "<<mapSize<<" tilesize: "<<tileSize<<" dimensions: "<<dimensions.getX()<<"x"<<dimensions.getY()<<std::endl;
        
        //trying to grab the textures here using the Tileset.hpp from the tmxlite library
        for (const auto& tileset : map.getTilesets()) {
            std::string texturePath =  tileset.getImagePath();  
            
            int tileWidth = tileset.getTileSize().x;
            int tileHeight = tileset.getTileSize().y;
            int columns = tileset.getColumnCount();
            int rows = tileset.getTileCount() / columns;
            std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(renderer, texturePath, Vector2(32, 32), rows, columns);
            spritesheet->setGID(tileset.getFirstGID(),tileset.getLastGID());
            
            spritesheets.emplace_back(spritesheet);
            
            
            // std::cout<<"tileset name: "<< tileset.getName()<<", first GID: " <<tileset.getFirstGID()<<", last GID: "<<tileset.getLastGID()<<", relative path to png: "<<tileset.getImagePath()<<std::endl;
            tilesets.emplace_back(tileset);
        }
    

        
        for (const auto& layer : map.getLayers()) {
            if (layer->getType() == tmx::Layer::Type::Tile) {
                const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
                // std::cout<<"layername: " <<tileLayer.getName()<<std::endl;
                const auto& tiles = tileLayer.getTiles();
                
                int x = 0, y = 0;
                for (const auto& tile : tiles) {
                    if (tile.ID > 0) {  
                        blocks.emplace_back(Vector2(x, y));
                        ids.emplace_back(tile.ID);
                    }
                    
                    x++;
                    if (x >= mapSize.x) {
                        x = 0;
                        y++;
                    }
                }
            }
        }
       
        // std::cout << "Loaded Level: " << mapSize.x << "x" << mapSize.y << " tiles.\n";
        // std::cout << "Loaded " << blocks.size() << " blocks from TMX.\n";
        // std::cout<<"# Tilesets "<< tilesets.size()<<std::endl;
        return true;
    }

};

#endif