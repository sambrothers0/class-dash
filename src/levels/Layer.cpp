#include "levels/Layer.hpp"
#include "SDL.h"

// gets global ID for a given block
uint32_t Layer::getID(const Vector2& block) const { 
    for (size_t i = 0; i < blocks.size(); ++i) {
        if (blocks[i] == block) { 
            return ids[i];         
        }
    }
    return 0;  
}