#ifndef GAME_FILE
#define GAME_FILE

#include <stdlib.h>
#include <unistd.h>
#include "../headers/gametable.h"

#define DEFAULT_SLEEP_TIME_USEC 500000 
#define MAX_PLAYERS 4

typedef struct GamePrivate GamePrivate;

typedef struct Game 
{
   void (*start)(struct Game *self);
   int (*setInitialCell)(struct Game *self, const Cell *cell);
   int (*addPlayer)(struct Game *self, Color color);
   void (*displayResult)(const GameTable *table);

   GamePrivate *p;
} Game;

Game* createGame(int sizeGameTableX, int sizeGameTableY);
void destroyGame(Game *self);

#endif

