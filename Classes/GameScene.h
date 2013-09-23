#ifndef __HexChain__GameScene__
#define __HexChain__GameScene__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
};

#endif /* defined(__HexChain__GameScene__) */
