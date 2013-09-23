#include "Game.h"
#include "cocos2d.h"

Game::Game()
{
    field = new Field();
    lastNumber = 0;
    
    filledBlocks = new bool*[FIELD_WIDTH];
    checkedBlocks = new bool*[FIELD_WIDTH];
    for (int x = 0; x < FIELD_WIDTH; x++) {
        filledBlocks[x] = new bool[FIELD_HEIGHT];
        checkedBlocks[x] = new bool[FIELD_HEIGHT];
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            filledBlocks[x][y] = false;
            checkedBlocks[x][y] = false;
        }
    }
    
    isChecking = false;
    lastChecked = new int[2];
    lastChecked[0] = 0;
    lastChecked[1] = 0;
}

Game::~Game()
{
    delete field; field = NULL;
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        delete[] filledBlocks[x]; filledBlocks[x] = NULL;
        delete[] checkedBlocks[x]; checkedBlocks[x] = NULL;
    }
    delete[] filledBlocks; filledBlocks = NULL;
    delete[] checkedBlocks; checkedBlocks = NULL;
    delete[] lastChecked;
}

Field* Game::getField()
{
    return field;
}

int Game::getLastNumber()
{
    return lastNumber;
}

bool** Game::getFilledBlocks()
{
    return filledBlocks;
}

bool** Game::getCheckedBlocks()
{
    return checkedBlocks;
}

// 消せるブロックかどうかチェック
// 前回チェックした要素と同じ色で近ければ消せる
bool Game::checkBlocks(int x, int y)
{
    // チェック済みなら何もしない
    if (checkedBlocks[x][y]) return false;
    
    // ブロック取得
    Block* block = field->getBlocks()[x][y];
    if (block == NULL) return false;
    
    // チェック開始
    if (isChecking == false) {
        isChecking = true;
    }
    // チェック中
    else {
        Block* lastBlock = field->getBlocks()[lastChecked[0]][lastChecked[1]];
        if (lastBlock == NULL) return false;
        
        // 色が違う
        if (block->getColor() != lastBlock->getColor()) return false;
    
        // 距離が遠い
        float distance  = sqrt( pow(((lastChecked[0] - x) * 2), 2) + pow((lastChecked[1] - y), 2) );
        float threshold = sqrt(5);
        if (distance > threshold) return false;
    }
    
    // 最終チェック要素の記録
    lastChecked[0] = x;
    lastChecked[1] = y;
    // チェック済みに
    checkedBlocks[x][y] = true;
    // チェック成功
    return true;
}

void Game::deleteCheckedBlocks()
{
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            if (checkedBlocks[x][y]) {
                delete field->getBlocks()[x][y];
                field->getBlocks()[x][y] = NULL;
            }
            checkedBlocks[x][y] = false;
        }
    }
    lastChecked[0] = 0;
    lastChecked[1] = 0;
    isChecking = false;
}

void Game::fillBlocks()
{
    Block*** b = field->getBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0 + x % 2; y < FIELD_HEIGHT; y += 2) {
            filledBlocks[x][y] = false;
            if (b[x][y] == NULL) {
                lastNumber++;
                b[x][y] = new Block(lastNumber, rand() % Block::kColor_Last);
                filledBlocks[x][y] = true;
            }
        }
    }
}

void Game::dropBlocks()
{
    Block*** b = field->getBlocks();
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0 + x % 2; y < FIELD_HEIGHT; y += 2) {
            if (b[x][y] == NULL) {
                for (int posY = y + 2; posY < FIELD_HEIGHT; posY += 2) {
                    if (b[x][posY] != NULL) {
                        b[x][y] = b[x][posY];
                        b[x][posY] = NULL;
                        break;
                    }
                }
            }
        }
    }
}