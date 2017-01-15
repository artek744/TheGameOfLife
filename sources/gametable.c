#include "gametable.h"

struct GameTablePrivate {
   int sizeTableX;
   int sizeTableY;
   Color **table;
};

static void setCell(GameTable *self, const Cell *cell)
{
   self->p->table[cell->x][cell->y] = cell->color;   
}

static Color getCell(const struct GameTable *self, int x, int y)
{
   return self->p->table[y][x];
}

static int getSizeX(const struct GameTable *self)
{
   return self->p->sizeTableX;   
}

static int getSizeY(const struct GameTable *self)
{
   return self->p->sizeTableY;
}

GameTable *createGameTable(int sizeX, int sizeY)
{
   GameTable *gameTable = malloc(sizeof(GameTable));
   
   gameTable->p = malloc(sizeof(GameTablePrivate));
   gameTable->p->sizeTableX = sizeX;
   gameTable->p->sizeTableY = sizeY;
   
   gameTable->p->table = (Color **) malloc(sizeX * sizeof(Color *));
   for(int i=0; i<sizeX; i++) {
      gameTable->p->table[i] = malloc(sizeY * sizeof(Color));
      for(int j=0; j<sizeY; j++) {
         gameTable->p->table[i][j] = NOCOLOR;
      }
   } 
   
   gameTable->getSizeX = &getSizeX;
   gameTable->getSizeY = &getSizeY;
   gameTable->setCell = &setCell;
   gameTable->getCell = &getCell;

   return gameTable;
}

void destroyGameTable(GameTable *self)
{
   for(int i=0; i<self->p->sizeTableX; i++) {
      free(self->p->table[i]);
   }
   free(self->p->table);
   free(self->p);
   free(self);
}


