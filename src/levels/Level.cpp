#include "levels/Level.hpp"


// gets global ID for a given block
uint32_t Level::getID(const Vector2& block) const { 
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (std::get<0>(blocks[i]) == block) { 
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
    // std::cout<<"mapsize: "<<mapSize<<" tilesize: "<<tileSize<<" dimensions: "<<dimensions.getX()<<"x"<<dimensions.getY()<<std::endl;
    
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

        
        // Iterate over tiles in the tileset
        for (const auto& tile : tileset.getTiles()) {
            // Get the global tile ID by adding first GID
            unsigned int globalID = tileset.getFirstGID() + tile.ID;
            
            // Check if this tile has any collision objects
            for (const auto& object : tile.objectGroup.getObjects()) {
                // for (const auto& object : objectGroup.objects) {
                    CollisionObject collObj;
                    
                    //Setup a locally based CollisionObject for a specific tile type
                    collObj.bounds.x = static_cast<int>(object.getAABB().left);
                    collObj.bounds.y = static_cast<int>(object.getAABB().top);
                    collObj.bounds.w = static_cast<int>(object.getAABB().width);
                    collObj.bounds.h = static_cast<int>(object.getAABB().height);
                    collObj.type = object.getClass();
                    collObj.name = object.getName();
                    
                    // Add a locally based CollisionObject for a specific gid
                    tileCollisions[globalID].push_back(collObj);
    
                // }
            }
        
            
        
        // Set up indexes of specific objects
        if (tileset.getName() == "objects") {
            auto first = tileset.getFirstGID();

            hitboxIDs.emplace(first); // Collision tile
        }
    }
}
    // std::cout<<"SIZE: "<<tileCollisions.size()<<std::endl;
    // for (const auto& [tileID, collisionList] : tileCollisions) {
    //     std::cout << "Tile ID: " << tileID << "\n";
        
    //     for (const auto& obj : collisionList) {
    //         std::cout << "  CollisionObject:\n";
    //         std::cout << "    Name: " << obj.name << "\n";
    //         std::cout << "    Type: " << obj.type << "\n";
    //         std::cout << "    Bounds: (x=" << obj.bounds.x
    //                   << ", y=" << obj.bounds.y
    //                   << ", w=" << obj.bounds.w
    //                   << ", h=" << obj.bounds.h << ")\n";
    //     }
    
    //     std::cout << std::endl;
    // }
    for (const auto& layer : map.getLayers()) {
        blocks.clear();
        ids.clear();
        
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles = tileLayer.getTiles();
            int x = 0, y = 0;
            for (std::size_t i = 0; i < tiles.size(); ++i) {
                const auto& tile = tiles[i];
            
                int x = i % mapSize.x;
                int y = i / mapSize.x;
            
                // std::cout << "Tile Index: " << x << " " << y << "Tile Layer: "<<tileLayer.getName()<<std::endl;
            
                uint32_t tileID = tile.ID;
            
                if (tileID == 0) continue;
            
                auto it = tileCollisions.find(tileID);
                if (it != tileCollisions.end()) {
            
                    for (const auto& objTemplate : it->second) {
                        CollisionObject worldObj = objTemplate;
                        worldObj.bounds.x += x * 32;
                        worldObj.bounds.y += y * 32;
            
                        std::cout << "    Adding collision object:"
                                  << " ID=" << tileID
                                  << " type=" << worldObj.type
                                  << ", name=" << worldObj.name
                                  << ", bounds=(" << worldObj.bounds.x << ", " << worldObj.bounds.y
                                  << ", " << worldObj.bounds.w << ", " << worldObj.bounds.h << ")"
                                  << std::endl;
            
                        collisionObjects.push_back(worldObj);
                    }
                }
            
                if (tile.ID > 0) {
                    if (tile.flipFlags != 0) {
                        blocks.emplace_back(Vector2(x, y), 1);
                        std::cout << "flip " << tile.ID << std::endl;
                    }
                    else {blocks.emplace_back(Vector2(x, y), 0);}
                    ids.emplace_back(tile.ID);
                }
            
            }
            
        std::shared_ptr<Layer> new_layer = std::make_shared<Layer>(blocks, ids, tileLayer.getName());
        layers.emplace_back(new_layer);
            }
        
    
    }
    return true;
}

const CollisionObject* Level::getLocalCollisionObject(const Vector2& position) const {
    
    for (const auto& layer : layers) {
        uint32_t gid = layer->getID(position);  // Get the GID for the tile at the given position

        if (isCollisionGID(gid)) {

            auto it = tileCollisions.find(gid);
            if (it != tileCollisions.end() && !it->second.empty()) {
                
                // if(position.get(X))
                std::cout << "Collide with " << it->second[0].name << std::endl;
                return &it->second[0];  
            }
        }
    }
    return nullptr;
}

const CollisionObject* Level::getWorldCollisionObject(const Vector2& position) const {
    
    for (const auto layer : layers) {
        uint32_t gid = layer->getID(position);
        if (isCollisionGID(gid)) {
            // std::cout<<"FOUND ID: "<<gid<<std::endl;
            // Calculate the tile's grid position
            int tileX = static_cast<int>(position.getX() );
            int tileY = static_cast<int>(position.getY() );
            // std::cout<<"TileX: "<<tileX<<" TileY: "<<tileY<<std::endl;
            // std::cout<<collisionObjects.size()<<std::endl;
            // Find the actual collision object in the world
            for (const auto& obj : collisionObjects) {
                // Calculate the tile position from the object's position
                int objTileX = obj.bounds.x /32;
                int objTileY = obj.bounds.y /32;
                // std::cout<<"collide X: "<<objTileX<<"collide Y" <<objTileY<<std::endl;
                
                // Check if this object is at the same tile position
                if (objTileX == tileX && objTileY == tileY) {
                    std::cout << "World collision object found at tile (" << tileX << "," << tileY << ")" << std::endl;
                    std::cout << "Global bounds: x=" << obj.bounds.x 
                              << " y=" << obj.bounds.y 
                              << " w=" << obj.bounds.w
                              << " h=" << obj.bounds.h 
                              << " type=" << obj.type <<" class=" <<obj.name
                              << std::endl;
                              return &obj;
                              
                }
            }
            
            
        }
    }
    return nullptr;
}
    // for (const auto& layer : layers) {
    //     uint32_t gid = layer->getID(position);  // Get the GID for the tile at the given position

    //     if (isCollisionGID(gid)) {

    //         auto it = tileCollisions.find(gid);
    //         if (it != tileCollisions.end() && !it->second.empty()) {
                
    //             // if(position.get(X))
    //             std::cout << "Collide with " << it->second[0].name << std::endl;
    //             return &it->second[0];  
    //         }
    //     }
    // }
    // return nullptr;


// bool Level::collidedWith(const Vector2& position) const {

// }

bool Level::colliderTileAt(const Vector2& position) const {
    // std::cout << "Total collision objects in world: " << collisionObjects.size() << std::endl;

    for (const auto layer : layers) {
        uint32_t gid = layer->getID(position);
        if (isCollisionGID(gid)) {
            // std::cout<<"FOUND ID: "<<gid<<std::endl;
            // Calculate the tile's grid position
            int tileX = static_cast<int>(position.getX() );
            int tileY = static_cast<int>(position.getY() );
            // std::cout<<"TileX: "<<tileX<<" TileY: "<<tileY<<std::endl;
            // std::cout<<collisionObjects.size()<<std::endl;
            // Find the actual collision object in the world
            for (const auto& obj : collisionObjects) {
                // Calculate the tile position from the object's position
                int objTileX = obj.bounds.x /32;
                int objTileY = obj.bounds.y /32;
                // std::cout<<"collide X: "<<objTileX<<"collide Y" <<objTileY<<std::endl;
                
                // Check if this object is at the same tile position
                if (objTileX == tileX && objTileY == tileY) {
                    std::cout << "World collision object found at tile (" << tileX << "," << tileY << ")" << std::endl;
                    std::cout << "Global bounds: x=" << obj.bounds.x 
                              << " y=" << obj.bounds.y 
                              << " w=" << obj.bounds.w
                              << " h=" << obj.bounds.h 
                              << " type=" << obj.type <<" class=" <<obj.name
                              << std::endl;
               return true; }
            }
            
            
        }
    }
    return false;
}