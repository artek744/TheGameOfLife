#include "../headers/game.h"

int main(int argc, char **argv) 
{
   int sizeGameTableX,sizeGameTableY;
   
   if(argc < 2) {
      sizeGameTableX = 20;
      sizeGameTableY = 20;
   } 
   else {
      sizeGameTableX = atoi(argv[1]);
      sizeGameTableY = atoi(argv[2]);
   }

   Game *game = createGame(sizeGameTableX, sizeGameTableY);
   
   game->addPlayer(game, RED);

   Cell *cell = createCell(RED, 1, 1);
   game->setInitialCell(game, cell);

   destroyCell(cell);
   game->start(game);   
   destroyGame(game);

   return 0;
}

