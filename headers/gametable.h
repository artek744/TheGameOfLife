#ifndef GAMETABLE_FILE
#define GAMETABLE_FILE

#include <stdlib.h>
#include <stdio.h>

#include "cell.h"

typedef struct GameTablePrivate GameTablePrivate; 

typedef struct GameTable
{
   void (*setCell)(struct GameTable *self, const Cell *cell); 
   Color (*getCell)(const struct GameTable *self, int x, int y);
   int (*getSizeX)(const struct GameTable *self);
   int (*getSizeY)(const struct GameTable *self);
   GameTablePrivate *p;

} GameTable;

GameTable* createGameTable(int sizeX, int sizeY);
void destroyGameTable(GameTable *self);



#endif
