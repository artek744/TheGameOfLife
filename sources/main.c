#include "../headers/game.h"

void setupGameTable(Game *game)
{
   Cell cell;
   cell = createCell(RED, 15, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 16, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 15, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 16, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 14, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 17, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 15, 14);
   game->setInitialCell(game, &cell);

   cell = createCell(YELLOW, 100, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 101, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 100, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 101, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 99, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 102, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(YELLOW, 101, 18);
   game->setInitialCell(game, &cell);

   cell = createCell(GREEN, 100, 42);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 101, 42);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 100, 44);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 101, 44);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 99, 43);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 102, 43);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 101, 45);
   game->setInitialCell(game, &cell);

   cell = createCell(BLUE, 15, 38);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 16, 38);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 15, 40);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 16, 40);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 14, 39);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 17, 39);
   game->setInitialCell(game, &cell);
   cell = createCell(BLUE, 15, 41);
   game->setInitialCell(game, &cell);
}

int main(int argc, char **argv) 
{
   int sizeGameTableX,sizeGameTableY;
   
   if(argc < 2) {
      sizeGameTableX = 110;
      sizeGameTableY = 110;
   } 
   else {
      sizeGameTableX = atoi(argv[1]);
      sizeGameTableY = atoi(argv[2]);
   }

   Game *game = createGame(sizeGameTableX, sizeGameTableY);
   
   game->addPlayer(game, RED);
   game->addPlayer(game, GREEN);
   game->addPlayer(game, YELLOW);
   game->addPlayer(game, BLUE);
   setupGameTable(game);

   game->start(game);   
   destroyGame(game);

   return 0;
}

