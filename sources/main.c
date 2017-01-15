#include "../headers/game.h"

void setupGameTable(Game *game)
{
   Cell cell;
   cell = createCell(RED, 5, 5);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 6, 5);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 5, 7);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 6, 7);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 4, 6);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 7, 6);
   game->setInitialCell(game, &cell);
   cell = createCell(RED, 5, 4);
   game->setInitialCell(game, &cell);

   cell = createCell(GREEN, 15, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 16, 15);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 15, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 16, 17);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 14, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 17, 16);
   game->setInitialCell(game, &cell);
   cell = createCell(GREEN, 15, 14);
   game->setInitialCell(game, &cell);

  
}

int main(int argc, char **argv) 
{
   int sizeGameTableX,sizeGameTableY;
   
   if(argc < 2) {
      sizeGameTableX = 45;
      sizeGameTableY = 45;
   } 
   else {
      sizeGameTableX = atoi(argv[1]);
      sizeGameTableY = atoi(argv[2]);
   }

   Game *game = createGame(sizeGameTableX, sizeGameTableY);
   
   game->addPlayer(game, RED);
   game->addPlayer(game, GREEN);
   setupGameTable(game);

   game->start(game);   
   destroyGame(game);

   return 0;
}

