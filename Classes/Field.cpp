#include "Field.h"

Field::Field()
{
    blocks = new Block**[FIELD_WIDTH];
    for (int x = 0; x < FIELD_WIDTH; x++) {
        blocks[x] = new Block*[FIELD_HEIGHT];
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            blocks[x][y] = NULL;
        }
    }
}

Field::~Field()
{
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            delete blocks[x][y]; blocks[x][y] = NULL;
        }
        delete[] blocks[x]; blocks[x] = NULL;
    }
    delete[] blocks; blocks = NULL;
}

Block*** Field::getBlocks()
{
    return blocks;
}