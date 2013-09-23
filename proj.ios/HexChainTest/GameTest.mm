#import "GameTest.h"
#import "Game.h"
#import "Config.h"

@implementation GameTest

- (void)testGame
{
    Game* g = new Game();
    
    STAssertTrue(g->getField()->getBlocks()[FIELD_WIDTH-1][FIELD_HEIGHT-1] == NULL, @"before fill field");
    STAssertTrue(g->getFilledBlocks()[FIELD_WIDTH-1][FIELD_HEIGHT-1] == false, @"before fill field");
    
    g->fillBlocks();
    
    for (int x = 0; x < FIELD_WIDTH; x++) {
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            //STAssertTrue(g->getField()->getBlocks()[x][y] == NULL, @"x:%d y:%d is null", x, y);
        }
    }
    
    STAssertTrue(g->getField()->getBlocks()[FIELD_WIDTH-1][FIELD_HEIGHT-1] != NULL, @"after fill field");
    STAssertTrue(g->getField()->getBlocks()[FIELD_WIDTH-1][FIELD_HEIGHT-1]->getNumber() == g->getLastNumber(), @"after fill field");
    STAssertTrue(g->getFilledBlocks()[FIELD_WIDTH-1][FIELD_HEIGHT-1] == true, @"after fill field");
}

- (void)testCheck
{
    Game* g = new Game();
    
    g->fillBlocks();
    g->getField()->getBlocks()[2][6] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[2][8] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[3][7] = new Block(1, Block::kColor_Blue);
    g->getField()->getBlocks()[3][9] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[4][6] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[4][8] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[4][10] = new Block(1, Block::kColor_Blue);
    g->getField()->getBlocks()[5][5] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[5][7] = new Block(1, Block::kColor_Red);
    g->getField()->getBlocks()[5][9] = new Block(1, Block::kColor_Blue);
    
    STAssertTrue(g->checkBlocks(4, 8), @"最初は true");
    STAssertTrue(!g->checkBlocks(2, 8), @"4,8 - 2,8 は遠いので false");
    STAssertTrue(!g->checkBlocks(4, 10), @"4,8 - 4,10 は色違いなので false");
    STAssertTrue(g->checkBlocks(5, 7), @"4,8 - 5,7 は true (斜め移動)");
    STAssertTrue(g->checkBlocks(5, 5), @"5,7 - 5,5 は true（上下移動）");

    g->deleteCheckedBlocks();
    
    STAssertTrue(g->getField()->getBlocks()[4][8] == NULL, @"deleted");
    STAssertTrue(g->getField()->getBlocks()[5][7] == NULL, @"deleted");
    STAssertTrue(g->getField()->getBlocks()[5][5] == NULL, @"deleted");
    
    g->dropBlocks();
    
    STAssertTrue(g->getField()->getBlocks()[4][8] != NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[5][7] != NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[5][5] != NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[4][18] == NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[5][17] == NULL, @"droped");
    STAssertTrue(g->getField()->getBlocks()[5][19] == NULL, @"droped");
}

@end
