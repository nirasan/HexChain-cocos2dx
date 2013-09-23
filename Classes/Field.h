#ifndef __HexChain__Field__
#define __HexChain__Field__

#include <iostream>
#include "Block.h"
#include "Config.h"

class Field
{
private:
    Block*** blocks;
    
public:
    Field();
    ~Field();

    Block*** getBlocks();
};

#endif /* defined(__HexChain__Field__) */
