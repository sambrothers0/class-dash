#include "levels/Level.hpp"
#include "gameDimensions.hpp"


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
    
    setDimensions(Vector2(mapSize.x * tileSize.x, mapSize.y * tileSize.y));
    std::cout<<"dimensions "<<getDimensions()<<std::endl;
    // dimensions = Vector2(mapSize.x * tileSize.x, mapSize.y * tileSize.y);
    
    //trying to grab the textures here using the Tileset.hpp from the tmxlite library
    for (const auto& tileset : map.getTilesets()) {
        std::string texturePath =  tileset.getImagePath();  
        std::cout << texturePath << std::endl;
        
        int columns = tileset.getColumnCount();
        int rows = tileset.getTileCount() / columns;
        std::shared_ptr<Spritesheet> spritesheet = std::make_shared<Spritesheet>(renderer, texturePath, Vector2(TILE_SIZE, TILE_SIZE), rows, columns);
        spritesheet->setGID(tileset.getFirstGID(),tileset.getLastGID());
        
        spritesheets.emplace_back(spritesheet);

        
        // Iterate over tiles in the tileset
        for (const auto& tile : tileset.getTiles()) {
            // Get the global tile ID by adding first GID
            unsigned int globalID = tileset.getFirstGID() + tile.ID;
            
            // Check if this tile has any collision objects
            for (const auto& object : tile.objectGroup.getObjects()) {
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
    
            }
        
            
        
        // Set up indexes of specific objects
        if (tileset.getName() == "objects") {
            auto first = tileset.getFirstGID();

            hitboxIDs.emplace(first); // Collision tile
        }
    }
}

    for (const auto& layer : map.getLayers()) {
        blocks.clear();
        ids.clear();
        if(layer->getType() == tmx::Layer::Type::Object)
            {
                const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
                const auto& objects = objectLayer.getObjects();
                for(const auto& object : objects)
                {
                    if(object.getName()=="Player"){playerspawn=Vector2(object.getPosition().x,object.getPosition().y-1);}

                    if(object.getType()=="EnemySpawn"){
                        enemyspawns.push_back(Vector2(object.getPosition().x,object.getPosition().y-1));
                        float trackStart = 0;
                        float trackEnd = 0;
                        bool shoots = false;
                        bool biker = false;
                            for (const auto& property : object.getProperties()) {
                                if (property.getName()=="trackStart"){
                                    trackStart = property.getFloatValue();
                                } else if (property.getName() == "trackEnd") {
                                    trackEnd =  property.getFloatValue();
                                } else if (property.getName() == "shoots") {
                                    shoots = property.getBoolValue();
                                } else if (property.getName() == "biker") {
                                    biker = property.getBoolValue();
                                }
                                
                            // std::cout<<"Property "<<property.getName()<<" Value "<<property.getFloatValue()<<" Object "<<object.getName()<<std::endl;
                            
                            
                        }

                        levelEnemyData.push_back(EnemyData(Vector2(object.getPosition().x,object.getPosition().y-1), trackStart, trackEnd, shoots, biker));
                    }

                    if (object.getType() == "CorgiSpawn") {
                        float trackStart = 0;
                        float trackEnd = 0;
                        for (const auto& property : object.getProperties()) {
                            if (property.getName()=="trackStart"){trackStart = property.getFloatValue();}
                            else if (property.getName() == "trackEnd"){trackEnd =  property.getFloatValue();}
                            std::cout<<"Property "<<property.getName()<<" Value "<<property.getFloatValue()<<" Object "<<object.getName()<<std::endl;
                        }

                        corgiData.push_back(EnemyData(
                            Vector2(object.getPosition().x, object.getPosition().y - 1),
                            trackStart,
                            trackEnd,
                            false,
                            false
                        ));
                    }

                    if (object.getName() == "Endpoint") {
                        levelEndPos = object.getPosition().x;
                    }

                    if (object.getType() == "Powerup") {

                        powerupData.push_back(EnemyData(
                            Vector2(object.getPosition().x, object.getPosition().y - 1),
                            object.getPosition().x,
                            object.getPosition().x,
                            false,
                            false
                        ));
                    }
                    

                        std::cout<<"Object Name: "<<object.getName()<<" ObjectLayer Name: "<<object.getPosition().x<<std::endl;
                                        }
                                    
            }
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles = tileLayer.getTiles();
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
                        worldObj.bounds.x += x * TILE_SIZE;
                        worldObj.bounds.y += y * TILE_SIZE;            
                        collisionObjects.push_back(worldObj);
                    }
                }
            
                if (tile.ID > 0) {
                    if (tile.flipFlags != 0) {
                        blocks.emplace_back(Vector2(x, y), 1);
                    }
                    else {blocks.emplace_back(Vector2(x, y), 0);}
                    ids.emplace_back(tile.ID);
                }
            
            }
            float opacity =1.0;
        if (tileLayer.getOpacity()){opacity=tileLayer.getOpacity();}
        std::shared_ptr<Layer> new_layer = std::make_shared<Layer>(blocks, ids, tileLayer.getName(), opacity);
        layers.emplace_back(new_layer);
            }
        
    
    }
    return true;
}

bool Level::loadData(GameLogic& gameLogic, LevelData& levelData, SDL_Renderer* renderer) {
    if (!loadFromTMX(levelData.getFilePath(), renderer)) {
        return false;
    }

    // Set up enemies
    enemies.clear();
    // for (auto enemyData : levelEnemyData ) {
    //     auto startPos = enemyData.getStartPos();
    //     std::cout<<"startPoint"<< startPos<<std::endl;
    // }
    // for (auto enemyData : levelData.getEnemies()) {
    for (auto enemyData : levelEnemyData) {
        auto startPos = enemyData.getStartPos();

        std::cout << enemyData.getStartPos() << ", " << enemyData.getTrackStart() << ", " << enemyData.getTrackEnd() << std::endl;

        Enemy enemy(
            gameLogic,
            enemyData.getStartPos(),
            enemyData.getTrackStart(),
            enemyData.getTrackEnd(),
            enemyData.getCanShoot(),
            enemyData.getIsBiker()
        );

        // Find a solid object along that line
        auto hitbox = enemy.getHitbox() + startPos;

        auto leftX = hitbox.getLeftX();
        auto rightX = hitbox.getRightX();
        auto centerX = (leftX + rightX) / 2.0;
        auto bottomY = hitbox.getBottomY();

        double targetY = 768;

        // We only really care about the center x here
        for (auto y = bottomY; y <= WINDOW_HEIGHT; y += TILE_SIZE / 2) {
            auto worldTile = getWorldCollisionObject(Vector2(floor(centerX / TILE_SIZE), floor(y / TILE_SIZE)));

            if (worldTile) {
                auto bounds = worldTile->bounds;
                targetY = bounds.y - ENEMY_HEIGHT / 2;
                enemy.setGroundLevel(targetY);
                break;
            }
        }

        enemies.push_back(std::make_shared<Enemy>(enemy));
    }

    for (auto corgiDataItem : corgiData) {
        auto startPos = corgiDataItem.getStartPos();

        Corgi corgi(
            corgiDataItem.getStartPos(),
            corgiDataItem.getTrackStart(),
            corgiDataItem.getTrackEnd()
        );

        // Find a solid object along that line
        auto hitbox = corgi.getHitbox() + startPos;

        auto leftX = hitbox.getLeftX();
        auto rightX = hitbox.getRightX();
        auto centerX = (leftX + rightX) / 2.0;
        auto bottomY = hitbox.getBottomY();

        double targetY = 768;

        // We only really care about the center x here
        for (auto y = bottomY; y <= WINDOW_HEIGHT; y += TILE_SIZE / 2) {
            auto worldTile = getWorldCollisionObject(Vector2(floor(centerX / TILE_SIZE), floor(y / TILE_SIZE)));

            if (worldTile) {
                auto bounds = worldTile->bounds;
                targetY = bounds.y - 32 / 2;
                corgi.setGroundLevel(targetY);
                break;
            }
        }

        corgis.push_back(std::make_shared<Corgi>(corgi));
    }


    for (auto powerupDataItem : powerupData) {
        auto startPos = powerupDataItem.getStartPos();

        Powerup powerup(
            powerupDataItem.getStartPos(),
            powerupDataItem.getTrackStart(),
            powerupDataItem.getTrackEnd()
        );

        // Find a solid object along that line
        auto hitbox = powerup.getHitbox() + startPos;

        auto leftX = hitbox.getLeftX();
        auto rightX = hitbox.getRightX();
        auto centerX = (leftX + rightX) / 2.0;
        auto bottomY = hitbox.getBottomY();

        double targetY = 768;

        // We only really care about the center x here
        for (auto y = bottomY; y <= WINDOW_HEIGHT; y += TILE_SIZE / 2) {
            auto worldTile = getWorldCollisionObject(Vector2(floor(centerX / TILE_SIZE), floor(y / TILE_SIZE)));

            if (worldTile) {
                auto bounds = worldTile->bounds;
                targetY = bounds.y - 32 / 2;
                powerup.setGroundLevel(targetY);
                break;
            }
        }
        std::cout<<"Adding powerup"<<std::endl;

        powerups.push_back(std::make_shared<Powerup>(powerup));
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

            // Calculate the tile's grid position
            int tileX = static_cast<int>(position.getX() );
            int tileY = static_cast<int>(position.getY() );
        
            // Find the actual collision object in the world
            for (const auto& obj : collisionObjects) {
                // Calculate the tile position from the object's position
                int objTileX = obj.bounds.x / TILE_SIZE;
                int objTileY = obj.bounds.y / TILE_SIZE;
                
                // Check if this object is at the same tile position
                if (objTileX == tileX && objTileY == tileY) {
                              return &obj;
                              
                }
            }
            
            
        }
    }
    return nullptr;
}

bool Level::colliderTileAt(const Vector2& position) const {

    for (const auto layer : layers) {
        uint32_t gid = layer->getID(position);
        if (isCollisionGID(gid)) {
            // Calculate the tile's grid position
            int tileX = static_cast<int>(position.getX() );
            int tileY = static_cast<int>(position.getY() );
           
            // Find the actual collision object in the world
            for (const auto& obj : collisionObjects) {
                // Calculate the tile position from the object's position
                int objTileX = obj.bounds.x / TILE_SIZE;
                int objTileY = obj.bounds.y / TILE_SIZE;
                // std::cout<<"collide X: "<<objTileX<<"collide Y" <<objTileY<<std::endl;
                
                // Check if this object is at the same tile position
                if (objTileX == tileX && objTileY == tileY) {
                   
               return true; }
            }
            
            
        }
    }
    return false;
}

void Level::removeDeadEnemies() {
    // Move the projectiles, while marking any which should be deleted
    std::vector<size_t> toDelete;

    for (size_t idx = 0; idx < enemies.size(); idx++) {
        auto enemy = enemies[idx];

        if (!enemy->isAlive()) {
            toDelete.push_back(idx);
        }
    }

    // Delete the corresponding indexes
    if (toDelete.size() > 0) {
        // This is needed to keep the indexes accurate
        int deleted = 0;

        for (auto idx : toDelete) {
            enemies.erase(enemies.begin() + idx - deleted);
            deleted++;
        }
    }
}

void Level::removeCollectedPowerups() {
    std::vector<size_t> toDelete;

    for (size_t idx = 0; idx < powerups.size(); idx++) {
        auto powerup = powerups[idx];
        if (!powerup->isActive()) {
        toDelete.push_back(idx);
        }
    }

    // Delete the corresponding indexes
    if (toDelete.size() > 0) {
        // This is needed to keep the indexes accurate
        int deleted = 0;

        for (auto idx : toDelete) {
            powerups.erase(powerups.begin() + idx - deleted);
            deleted++;
        }
    }
    
}