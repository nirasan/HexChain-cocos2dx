#include "GameScene.h"

using namespace cocos2d;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    initGame();
    
    // touch enable
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    return true;
}

void GameScene::initGame()
{
    game = new Game();
    fillBlocks();
    updateScore();
}

void GameScene::updateScore()
{
    char str[] = "0000000";
    sprintf(str, "%07d", game->getScore());
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCLabelTTF* score = (CCLabelTTF*)this->getChildByTag(TAG_SCORE);
    if (score == NULL) {
        score = CCLabelTTF::create(str, "Arial", 18.0);
        score->setPosition(ccp(size.width * 0.1, size.height * 0.8));
        score->setTag(TAG_SCORE);
        this->addChild(score);
    } else {
        score->setString(str);
    }
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
    
    CCRepeatForever* blink = CCRepeatForever::create(CCBlink::create(1, 2));
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0 + x % 2; y < FIELD_HEIGHT; y += 2) {
            Block* b = game->getField()->getBlocks()[x][y];
            CCLabelTTF* l = (CCLabelTTF*)this->getChildByTag(b->getNumber());
            if (!l) continue;
            CCRect rect = l->boundingBox();
            if (rect.containsPoint(touchPoint)) {
                CCLOG("[ccTouchMoved] x:%d y:%d", x, y);
                if (game->checkBlocks(x, y)) {
                    CCLOG("[ccTouchMoved][checked] x:%d y:%d", x, y);
                    l->runAction(blink);
                }
                return;
            }
        }
    }
}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    deleteBlocks();
}

void GameScene::deleteBlocks()
{
    bool** checkedBlocks = game->getCheckedBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0 + x % 2; y < FIELD_HEIGHT; y += 2) {
            if (checkedBlocks[x][y]) {
                Block* b = game->getField()->getBlocks()[x][y];
                this->removeChildByTag(b->getNumber());
            }
        }
    }
    
    game->deleteCheckedBlocks();
    
    updateScore();
    
    game->dropBlocks();
    
    fillBlocks();
}

void GameScene::fillBlocks()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // ブロックを埋める（ロジック側）
    game->fillBlocks();
    bool** filled = game->getFilledBlocks();
    
    // ロジック側で埋めたブロックのノードを画面外に作成する
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0 + x % 2; y < FIELD_HEIGHT; y += 2) {
            if (filled[x][y]) {
                Block* b = game->getField()->getBlocks()[x][y];
                
                CCLabelTTF* l = CCLabelTTF::create("■", "Arial", 24.0);
                l->setPosition(ccp(size.width  * (0.32 + x * FIELD_WIDTH_INTERVAL),
                                   size.height * (0.1 + (y + FIELD_HEIGHT) * FIELD_HEIGHT_INTERVAL)));
                l->setTag(b->getNumber());
                switch (b->getColor()) {
                    case Block::kColor_Red:    l->setColor(ccc3(255,   0,   0)); break;
                    case Block::kColor_Green:  l->setColor(ccc3(  0, 255,   0)); break;
                    case Block::kColor_Blue:   l->setColor(ccc3(  0,   0, 255)); break;
                    case Block::kColor_Yellow: l->setColor(ccc3(255, 255,   0)); break;
                    case Block::kColor_Purple: l->setColor(ccc3(255,   0, 255)); break;
                    default: break;
                }
                this->addChild(l);
            }
        }
    }
    
    // 全ブロックをロジック側の設置位置にあわせる
    // 既存のブロックで消えたブロックの上のものは落下し、新規ブロックは上から落ちてくる
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            Block* b = game->getField()->getBlocks()[x][y];
            if (b != NULL) {
                CCLabelTTF* l = (CCLabelTTF*)this->getChildByTag(b->getNumber());
                CCMoveTo* action = CCMoveTo::create(0.3,
                                                    ccp(size.width  * (0.32 + x * FIELD_WIDTH_INTERVAL),
                                                        size.height * (0.1  + y * FIELD_HEIGHT_INTERVAL)));
                l->runAction(action);
            }
        }
    }
}


