#include "levels/Level.hpp"

// gets global ID for a given block
uint32_t Level::getID(const Vector2& block) const { 
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == block) { 
            return ids[i];         
        }
    }
    return 0;  
}

// gets the correct spritesheet given a specific global ID
std::shared_ptr<Spritesheet> Level::getSpritesheetForGID(uint32_t gid) {
    for (const auto& spritesheet : spritesheets) {
        if (spritesheet->containsID(gid)) {
            return spritesheet;
        }
    }
    return nullptr; // No matching spritesheet found
}

// loads map from tmx file, and populates spritesheets, blocks, and ids
// later should be adjusted to account for layering and flip flags
bool Level::loadFromTMX(const std::string& filename, SDL_Renderer* renderer) {
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
        std::cout << texturePath << std::endl;
        
        int tileWidth = tileset.getTileSize().x;
        int tileHeight = tileset.getTileSize().y;
        int columns = tileset.getColumnCount();
        int rows = tileset.getTileCount() / columns;
        std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(renderer, texturePath, Vector2(32, 32), rows, columns);
        spritesheet->setGID(tileset.getFirstGID(),tileset.getLastGID());
        
        spritesheets.emplace_back(spritesheet);

        // Set up indexes of specific objects
        if (tileset.getName() == "objects") {
            auto first = tileset.getFirstGID();

            hitboxIDs.emplace(first); // Collision tile
        }
    }
    
    for (const auto& layer : map.getLayers()) {
        blocks.clear();
        ids.clear();
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
        std::shared_ptr<Layer> new_layer = std::make_shared<Layer>(blocks, ids);
        layers.emplace_back(new_layer);
        
    }
    
    // std::cout << "Loaded Level: " << mapSize.x << "x" << mapSize.y << " tiles.\n";
    // std::cout << "Loaded " << blocks.size() << " blocks from TMX.\n";
    // std::cout<<"# Tilesets "<< tilesets.size()<<std::endl;
    return true;
}