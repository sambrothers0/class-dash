#ifndef _MAPLOADER_H
#define _MAPLOADER_H


#include <tinyxml2.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

struct Tile {
    int id;
    int x, y;
};

class MapLoader {
public:
    bool loadMap(const std::string& filename);
    const std::vector<Tile>& getTiles() const { return layers; }
    std::string getTilesetPathForTileID(int tileID) const;
private:
    std::vector<Tile> layers;
    std::vector<std::pair<int, std::string>> tilesets; 
    int mapWidth, mapHeight, tileSize;

};

#endif
