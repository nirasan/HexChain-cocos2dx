#ifndef __HexChain__GameScene__
#define __HexChain__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Game.h"

USING_NS_CC;

class GameScene : public cocos2d::CCLayer
{
private:
    Game* game;
    
    int time;
    
    void initGame();
    
    void initTime();
    void updateTime();
    
    void updateScore();
    
    void fillBlocks();    
    void deleteBlocks();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchMoved(CCTouch* pTouch, CCEvent* pEvent);
    void ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent);
};

#endif /* defined(__HexChain__GameScene__) */
