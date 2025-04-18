#include "levels/Layer.hpp"
#include "SDL.h"

// gets global ID for a given block
uint32_t Layer::getID(const Vector2& block) const { 
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (std::get<0>(blocks[i]) == block) { 
            return ids[i];         
        }
    }
    return 0;  
}

bool Layer::hasFlipFlag(const Vector2& block) const {
    uint32_t gid = getID(block);
    for (auto tile : layerTiles) {
        std::cout<<tile.ID<<"here"<<std::endl;
        if (tile.flipFlags !=0){
            std::cout<<"Flipped"<<std::endl;
        }
    }

    const uint32_t H_FLIP = 0x80000000;



    return (gid & H_FLIP ) != 0;
}

