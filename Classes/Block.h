#ifndef __HexChain__Block__
#define __HexChain__Block__

#include <iostream>

class Block
{
private:
    int number;
    int color;
    
public:
    Block(int number, int color);
    ~Block();
    
    int getNumber();
    int getColor();
    
    enum kColor {
        kColor_Red,
        kColor_Blue,
        kColor_Green,
        kColor_Yellow,
        kColor_Purple,
    };
};


#endif /* defined(__HexChain__Block__) */
