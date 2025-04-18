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

uint32_t Layer::getID(int index) const {
    return ids[index];
}

bool Layer::hasFlipFlag(int index) const {
    uint32_t gid = getID(index);
    
    // for (auto tile : layerTiles) {
    //     std::cout<<tile.ID<<"here"<<std::endl;
    //     if (tile.flipFlags !=0){
    //         std::cout<<"Flipped"<<std::endl;
    //     }
    // }

    const uint32_t H_FLIP = 0x80000000;
    const uint32_t V_FLIP = 0x40000000;
    const uint32_t D_FLIP = 0x20000000;



    return (gid & (H_FLIP | V_FLIP | D_FLIP)) != 0;
}

