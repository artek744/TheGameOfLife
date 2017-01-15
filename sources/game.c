#include "../headers/game.h"

#define COLOR_RED  "\x1B[31m"
#define COLOR_GREEN  "\x1B[32m"
#define COLOR_YELLOW  "\x1B[33m"
#define COLOR_BLUE  "\x1B[34m"
#define COLOR_WHITE  "\x1B[37m"

struct GamePrivate
{
   GameTable *mainTable;
   GameTable *tmpTable;
   int playerCount;
   Color *players;
};

static void printCell(Color color)
{
   switch(color) {
      case RED: 
         printf("%so ", COLOR_RED);
         break;
      case GREEN:
         printf("%so ", COLOR_GREEN);
         break;
      case YELLOW:
         printf("%so ", COLOR_YELLOW);
         break;
      case BLUE:
         printf("%so ", COLOR_BLUE);
         break;
      default:
         printf("%so ", COLOR_WHITE);
   }
}

static void swapTables(GameTable *mainTable, GameTable *tmpTable)
{ 
   for(int y=0; y<tmpTable->getSizeY(tmpTable); y++) {
      for(int x=0; x<tmpTable->getSizeX(tmpTable); x++) {
         Cell cell = tmpTable->getCell(tmpTable, x, y);
         mainTable->setCell(mainTable, &cell);
      }
   }
   
   for(int y=0; y<tmpTable->getSizeY(tmpTable); y++) {
      for(int x=0; x<tmpTable->getSizeX(tmpTable); x++) {
         Cell cell = createCell(NOCOLOR, x, y);
         tmpTable->setCell(tmpTable, &cell);
      }
   }
}

static int getNeighborCount(const GameTable *table, const Cell *cell)
{
   int counter=0;
   for(int y=cell->y-1; y<=cell->y+1; y++) {
      for(int x=cell->x-1; x<=cell->x+1; x++) {
         
         if(x == cell->x && y == cell->y) {
            continue;
         }
        
         if(table->getCell(table, x, y).color == cell->color) {
            counter += 1;
         }
      }
   }
  return counter;
}

static void setCellsInTable(GameTable *mainTable, GameTable *tmpTable, Color player)
{
   for(int y=1; y<mainTable->getSizeY(mainTable)-1; y++) {
      for(int x=1; x<mainTable->getSizeX(mainTable)-1; x++) {
         
         Cell cell = createCell(player, x, y);
         int neighborCount = getNeighborCount(mainTable, &cell);
        
         if(mainTable->getCell(mainTable, x, y).color == NOCOLOR) {
            if(neighborCount == 3) {
               tmpTable->setCell(tmpTable, &cell);
            }
         }
         else if(mainTable->getCell(mainTable, x, y).color == player) {
            if(neighborCount == 2 || neighborCount == 3) {
               tmpTable->setCell(tmpTable, &cell);
            }
            else {
               cell.color = NOCOLOR;
               tmpTable->setCell(tmpTable, &cell);
            }
         }
      }
   }
}

static void startGame(Game *self)
{
   while(1) {
      self->displayResult(self->p->mainTable);
      usleep(DEFAULT_SLEEP_TIME_USEC);
      
      for(int i=0; i<self->p->playerCount; i++) {
         setCellsInTable(self->p->mainTable, self->p->tmpTable, self->p->players[i]);    
      }  
      swapTables(self->p->mainTable, self->p->tmpTable);   
   }
}


static int addPlayer(Game *self, Color color)
{
   if(self->p->playerCount + 1 > MAX_PLAYERS) {
      return -1;
   }

   self->p->playerCount++;
   self->p->players = realloc(self->p->players, self->p->playerCount * sizeof(Color));
   self->p->players[self->p->playerCount-1] = color;

   return 0;
}

static int getPlayerIndexByColor(Game *self, Color playerColor)
{
   int index = -1;
   
   for(int i=0; i<self->p->playerCount; i++) {
      if(self->p->players[i] == playerColor) {
         return i;   
      }
   }

   return index;
}

static int setInitialCell(Game *self, const Cell *cell)
{
   int playerIndex = getPlayerIndexByColor(self, cell->color);
   if(playerIndex == -1) {
      return -1;
   }

   self->p->mainTable->setCell(self->p->mainTable, cell);
   return 0;
}

static void displayResult(const GameTable *table)
{
   printf("\e[1;1H\e[2J");
   printf("  ");
   for(int x=0; x<table->getSizeX(table); x++){
      printf("%d ", x%10);
   }
   printf("\n");
   for(int y=0; y<table->getSizeY(table); y++) {
      printf("%d ", y%10);
      for(int x=0; x<table->getSizeX(table); x++) {
         Cell cell = table->getCell(table, x ,y);
         printCell(cell.color);
      }
      printf("\n");
   }
   printf("\n");
}

Game *createGame(int sizeGameTableX, int sizeGameTableY)
{
   Game *game = malloc(sizeof(Game));
   
   game->p = malloc(sizeof(GamePrivate));
   game->p->mainTable = createGameTable(sizeGameTableX, sizeGameTableY);
   game->p->tmpTable = createGameTable(sizeGameTableX, sizeGameTableY);
   game->p->playerCount = 0;
   game->p->players = calloc(0, sizeof(Color));

   game->start = &startGame;
   game->addPlayer = &addPlayer;
   game->setInitialCell = &setInitialCell;
   game->displayResult = &displayResult;
   
   return game;
}

void destroyGame(Game *self)
{
   destroyGameTable(self->p->mainTable);
   destroyGameTable(self->p->tmpTable);
   
   free(self->p->players);
   free(self->p);
   free(self);
}
