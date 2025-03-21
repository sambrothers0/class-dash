#include "MapLoader.hpp"


using namespace tinyxml2;
using namespace std;


// Flip flags (from TMX format)
const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
const unsigned TILE_ID_MASK = 0x1FFFFFFF; // Extracts the actual tile ID (29-bit)

bool MapLoader::loadMap(const std::string& filename) {
    XMLDocument doc;
    if (doc.LoadFile(filename.c_str()) != XML_SUCCESS) {
        cerr << "MAPLOADERCPP: Failed to load map file: " << filename << endl;
        return false;
    }
    XMLElement* mapElement = doc.FirstChildElement("map");
    if (!mapElement) {
        cerr << "MAPLOADERCPP: Map element not found" << endl;
        return false;
    }

    mapWidth = mapElement->IntAttribute("width");
    mapHeight = mapElement->IntAttribute("height");
    tileSize = mapElement->IntAttribute("tilewidth");

    cout << "Map dimensions: " << mapWidth << "x" << mapHeight << " tiles" << endl;
    cout << "Tile size: " << tileSize << "x" << tileSize << " pixels" << endl;

    XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    cout<<"tileset: "<<tilesetElement<<endl;
    XMLElement* layerElement = mapElement->FirstChildElement("layer");
    while (layerElement) {
        string layerName = layerElement->Attribute("name");
        cout << "LayerName: " << layerName << endl;
        XMLElement* dataElement = layerElement->FirstChildElement("data");
        if (dataElement && string(dataElement->Attribute("encoding")) == "csv") {
            const char* csvData = dataElement->GetText();
            
            stringstream ss(csvData);
            string tileId;
            vector<int> tiles;
            while (getline(ss, tileId, ',')) {
                unsigned long long rawId = stoull(tileId); 

                
                bool flippedHorizontally = rawId & FLIPPED_HORIZONTALLY_FLAG;
                bool flippedVertically = rawId & FLIPPED_VERTICALLY_FLAG;
                bool flippedDiagonally = rawId & FLIPPED_DIAGONALLY_FLAG;

                unsigned tileID = rawId & TILE_ID_MASK;

                tiles.push_back(tileID); 

            }
            cout << "Layer: " << layerName << ", tile count: " << tiles.size() << endl;
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }
    return 0;
}
