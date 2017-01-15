#include "gametable.h"

struct GameTablePrivate {
   int sizeTableX;
   int sizeTableY;
   Color **table;
};

static void setCell(GameTable *self, const Cell *cell)
{
   self->p->table[cell->y][cell->x] = cell->color;   
}

static Cell getCell(const struct GameTable *self, int x, int y)
{
   Cell cell = createCell(self->p->table[y][x], x, y);
   return cell;
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
   
   gameTable->p->table = (Color **) malloc(sizeY * sizeof(Color *));
   for(int y=0; y<sizeY; y++) {
      gameTable->p->table[y] = malloc(sizeY * sizeof(Color));
      for(int x=0; x<sizeX; x++) {
         gameTable->p->table[y][x] = NOCOLOR;
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
   for(int y=0; y<self->p->sizeTableY; y++) {
      free(self->p->table[y]);
   }
   free(self->p->table);
   free(self->p);
   free(self);
}


