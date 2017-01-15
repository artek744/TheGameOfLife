#include "../headers/game.h"

struct GamePrivate
{
   GameTable *tab1;
   GameTable *tab2;
   GameTable *currentTable;
   int playerCount;
   Color *players;
};

static void swapTables(GameTable *tab1, GameTable *tab2)
{
   GameTable tmp = *tab1;
   *tab1 = *tab2;
   *tab2 = tmp;
}

static void startGame(Game *self)
{  
   printf("Display table1.\n");
   self->displayResult(self->p->tab1);
   printf("display table2.\n");
   self->displayResult(self->p->tab2);
   sleep(1);   
   Cell *cell = createCell(BLUE, 1, 3);
   self->p->tab1->setCell(self->p->tab1, cell);
   printf(" ----- SWAP TABLES -----\n\n");
   swapTables(self->p->tab1, self->p->tab2);
   printf("Display table1.\n");
   self->displayResult(self->p->tab1);
   printf("Display table2.\n");
   self->displayResult(self->p->tab2);
   
   destroyCell(cell);
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

   self->p->currentTable->setCell(self->p->currentTable, cell);
   return 0;
}

static void displayResult(const GameTable *table)
{
//   char *clearConsole = "\033[2J\033[1;1H";
//   printf("%s", clearConsole);
   for(int i=0; i<table->getSizeX(table); i++) {
      for(int j=0; j<table->getSizeY(table); j++) {
         printf("%d ", (int)table->getCell(table, i, j));
      }
      printf("\n");
   }
   printf("\n");
}

Game *createGame(int sizeGameTableX, int sizeGameTableY)
{
   Game *game = malloc(sizeof(Game));
   
   game->p = malloc(sizeof(GamePrivate));
   game->p->tab1 = createGameTable(sizeGameTableX, sizeGameTableY);
   game->p->tab2 = createGameTable(sizeGameTableX, sizeGameTableY);
   game->p->playerCount = 0;
   game->p->players = calloc(0, sizeof(Color));
   game->p->currentTable = game->p->tab1;

   game->start = &startGame;
   game->addPlayer = &addPlayer;
   game->setInitialCell = &setInitialCell;
   game->displayResult = &displayResult;
   
   return game;
}

void destroyGame(Game *self)
{
   destroyGameTable(self->p->tab1);
   destroyGameTable(self->p->tab2);
   
   free(self->p->players);
   free(self->p);
   free(self);
}
