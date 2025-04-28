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
#include <tmxlite/Property.hpp>
#include "sprites/Spritesheet.hpp"
#include "physics/BoundingBox.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "Layer.hpp"
#include <tuple>
#include "characters/Enemy.hpp"
#include "levels/LevelData.hpp"
#include "characters/Corgi.hpp"


// Structure to represent a tsx object
struct CollisionObject {
    SDL_Rect bounds;
    std::string type;
    std::string name;
};




// Class for the current level's data
class Level {
    private:
    Vector2 dimensions;
    // For now the level is just going to have a few blocks to be drawn (this is temporary)
    // These are relative coordinates multiplied by 32 for drawing, to make it easier to define manually
    std::vector<std::tuple<Vector2,int>> blocks; // int will be 1 if there is a flip flag for the tile

    std::vector<std::shared_ptr<Spritesheet>> spritesheets;
    std::vector<uint32_t> ids;
    std::vector<std::shared_ptr<Layer>> layers;

    // List of GIDs of hitboxes
    std::set<uint32_t> hitboxIDs;

    // Store all collision objects in the world with globally based coordinates
    std::vector<CollisionObject> collisionObjects;

    // Store tile IDs with their respective collision object with local coordinates (ie: since the bounds for a grass block are the full sqaure, x:0, y:0, w:32, h:32)
    std::unordered_map<uint32_t, std::vector<CollisionObject>> tileCollisions;

    // List of enemy entities
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Corgi>> corgis;

    //List of EnemyData
    std::vector<EnemyData> levelEnemyData;

    // Corgis have the same properties as enemies but don't hurt the player
    std::vector<EnemyData> corgiData;

    // X-position that triggers the end of the level
    double levelEndPos = 1000000; // Replace this when loading the level

    Vector2 playerspawn;
    std::vector<Vector2> enemyspawns;
    public:
    explicit Level() {}
    void setDimensions(const Vector2& dims)  {
        dimensions = dims;
    }

    const Vector2& getDimensions() const {
        return dimensions;
    }

    Vector2 getPlayerSpawnPoint() const {
        return playerspawn;
    }
    std::vector<Vector2> getEnemySpawnPoints() const {
        return enemyspawns;
    }
    std::vector<std::tuple<Vector2,int>>& getBlocks() {
        return blocks;
    }

    std::unordered_map<unsigned int, std::vector<CollisionObject>>& getTileCollisions() {
        return tileCollisions;
    }

    std::vector<std::shared_ptr<Layer>>& getLayers() {
        return layers;
    }

    std::vector<std::shared_ptr<Enemy>>& getEnemies() {
        return enemies;
    }

    std::vector<std::shared_ptr<Corgi>>& getCorgis() {
        return corgis;
    }

    double getLevelEndPos() const {
        return levelEndPos;
    }

    // gets global ID for a given block
    uint32_t getID(const Vector2& block) const;

    // returns the CollisionObject with Local Bounds
    const CollisionObject* getLocalCollisionObject(const Vector2& position) const;

    // returns the ColliisonObject with World Bounds
    const CollisionObject* getWorldCollisionObject(const Vector2& position) const;

  
    void setBlocks(const std::vector<std::tuple<Vector2, int>>& _blocks) {
        blocks = _blocks;
    }

    // Does the list of hitbox IDs contain the given gid?
    bool isHitboxGID(uint32_t gid) const {
        return hitboxIDs.find(gid) != hitboxIDs.end();
    }

    // Does the tile ID has collisions associated with it?
    bool isCollisionGID(uint32_t gid) const {
        return tileCollisions.find(gid) !=tileCollisions.end();
    }

    // bool collidedWith(const Vector2& position) const;
    // Returns if there is a tile at the given position with a collider
    bool colliderTileAt(const Vector2& position) const;

    // gets the correct spritesheet given a specific global ID
    std::shared_ptr<Spritesheet> getSpritesheetForGID(uint32_t gid);

    // loads map from tmx file, and populates spritesheets, blocks, and ids
    // later should be adjusted to account for layering and flip flags
    bool loadFromTMX(const std::string& filename, SDL_Renderer* renderer);

    // Loads the level using the level data
    bool loadData(LevelData& levelData, SDL_Renderer* renderer);

    // Removes all enemies that died during the last tick
    void removeDeadEnemies();

    ~Level() {}
};

#endif