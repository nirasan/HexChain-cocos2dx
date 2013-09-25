#ifndef __HexChain__Game__
#define __HexChain__Game__

#include <iostream>
#include <math.h>
#include "Field.h"
#include "Block.h"
#include "Config.h"
//#include "cocos2d.h"

class Game
{
private:
    Field* field;
    int lastNumber;
    bool** filledBlocks;
    bool** checkedBlocks;
    
    bool isChecking;
    int* lastChecked;
    
    int score;
    
public:
    Game();
    ~Game();
    
    Field* getField();
    int getLastNumber();
    bool** getFilledBlocks();
    bool** getCheckedBlocks();
    int getScore();
    
    bool checkBlocks(int x, int y);
    void deleteCheckedBlocks();
    
    void fillBlocks();
    void dropBlocks();
};

#endif /* defined(__HexChain__Game__) */
