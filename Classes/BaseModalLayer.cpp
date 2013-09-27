#include "BaseModalLayer.h"

// モーダルレイヤの優先順位
#define kModalLayerPriority kCCMenuHandlerPriority-1
// モーダルレイア上のCCMenuの優先順位
#define kModalLayerMenuPriority kCCMenuHandlerPriority-2

bool BaseModalLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchPriority(kModalLayerPriority);
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite* frame = CCSprite::create("frame.png");
    frame->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
    this->addChild(frame);
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "tg_close_1.png",
                                                          "tg_close_2.png",
                                                          this,
                                                          menu_selector(BaseModalLayer::menuCloseCallback) );
    pCloseItem->setPosition(ccp(
                                visibleSize.width/2+frame->getContentSize().width/2-pCloseItem->getContentSize().width/2-10,
                                visibleSize.height/2+frame->getContentSize().height/2-pCloseItem->getContentSize().height/2-10));
    
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setTouchPriority(kModalLayerMenuPriority);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu);
    
    return true;
}

bool BaseModalLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
    // can not touch on back layers
    return true;
}

void BaseModalLayer::menuCloseCallback(CCObject* pSender)
{
    this->removeFromParentAndCleanup(true);
}
