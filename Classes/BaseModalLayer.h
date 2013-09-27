#ifndef __HexChain__BaseModalLayer__
#define __HexChain__BaseModalLayer__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class BaseModalLayer : public CCLayer
{
public:
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CREATE_FUNC(BaseModalLayer);
};

#endif /* defined(__HexChain__BaseModalLayer__) */
