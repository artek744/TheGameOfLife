#ifndef GAME_FILE
#define GAME_FILE

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <X11/Xlib.h>
#include <omp.h>
#include "../headers/gametable.h"

#define DEFAULT_SLEEP_TIME_USEC 200000
#define MAX_PLAYERS 4

#define COLOR_RED  "#FF0000"
#define COLOR_GREEN  "#00FF00"
#define COLOR_YELLOW  "#FFFF00"
#define COLOR_BLUE  "#428AFF"
#define COLOR_BLACK "#000000"
#define COLOR_DARK_GRAY "#696969"
#define COLOR_DIM_GRAY "#1e1e1e"
#define COLOR_LIGHT_GRAY "#D3D3D3"

#define HEIGHT_CELL 10
#define WIDTH_CELL 10

typedef struct GamePrivate GamePrivate;

typedef struct Game 
{
   int (*start)(struct Game *self);
   int (*setInitialCell)(struct Game *self, const Cell *cell);
   int (*addPlayer)(struct Game *self, Color color);

   GamePrivate *p;
} Game;

Game* createGame(int sizeGameTableX, int sizeGameTableY);
void destroyGame(Game *self);

#endif

