#include "../headers/game.h"

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

typedef struct ColorPallete
{
    XColor red;
    XColor green;
    XColor black;
    XColor white;
    XColor yellow;
    XColor blue;
    XColor lightGray;
    XColor darkGray;
    XColor dimGray;
} ColorPallete;

struct GamePrivate
{
   GameTable *mainTable;
   GameTable *tmpTable;
   int playerCount;
   Color *players;
   Display *display;
   int screen;
   Window mainWindow, gameArea;
   XEvent xev;
   ColorPallete color;
};

static void initColorPallete(Display *display, int screen, ColorPallete *color)
{
    Colormap colormap;
    colormap = DefaultColormap(display, screen);

    XParseColor(display, colormap, COLOR_GREEN, &color->green);
    XAllocColor(display, colormap, &color->green);

    XParseColor(display, colormap, COLOR_RED, &color->red);
    XAllocColor(display, colormap, &color->red);

    XParseColor(display, colormap, COLOR_BLUE, &color->blue);
    XAllocColor(display, colormap, &color->blue);

    XParseColor(display, colormap, COLOR_BLACK, &color->black);
    XAllocColor(display, colormap, &color->black);

    XParseColor(display, colormap, COLOR_YELLOW, &color->yellow);
    XAllocColor(display, colormap, &color->yellow);

    XParseColor(display, colormap, COLOR_LIGHT_GRAY, &color->lightGray);
    XAllocColor(display, colormap, &color->lightGray);

    XParseColor(display, colormap, COLOR_DARK_GRAY, &color->darkGray);
    XAllocColor(display, colormap, &color->darkGray);

    XParseColor(display, colormap, COLOR_DIM_GRAY, &color->dimGray);
    XAllocColor(display, colormap, &color->dimGray);
}

static void setFullScreen(Display *display, Window window, XEvent xev)
{
    Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    memset(&xev, 0, sizeof(xev));
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;
    XSendEvent (display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
}

static void drawRectanle(Game *self, const Cell *cell, const unsigned long color)
{
    XSetForeground(self->p->display, DefaultGC(self->p->display, self->p->screen), color);
    XFillRectangle(self->p->display, self->p->gameArea, DefaultGC(self->p->display, self->p->screen), cell->x*WIDTH_CELL, cell->y*HEIGHT_CELL, WIDTH_CELL, HEIGHT_CELL);
}

static void displayCell(Game *self, const Cell *cell)
{
   switch(cell->color) {
      case RED:
        drawRectanle(self, cell, self->p->color.red.pixel);
         break;
      case GREEN:
        drawRectanle(self, cell, self->p->color.green.pixel);
         break;
      case YELLOW:
        drawRectanle(self, cell, self->p->color.yellow.pixel);
         break;
      case BLUE:
        drawRectanle(self, cell, self->p->color.blue.pixel);
         break;
   default:
       break;
   }
}

static void displayResult(Game *self, const GameTable *table)
{
   XClearWindow(self->p->display, self->p->gameArea);
   for(int y=0; y<table->getSizeY(table); y++) {
      for(int x=0; x<table->getSizeX(table); x++) {
         Cell cell = table->getCell(table, x ,y);
         displayCell(self, &cell);
      }
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

static int startGame(Game *self)
{
   while(1) {
       XNextEvent(self->p->display, &self->p->xev);

       if(self->p->xev.type == KeyPress) {
           printf("%d\n", self->p->xev.xkey.keycode);
           if(self->p->xev.xkey.keycode == 65) {
                break;
           }
       }

       if(self->p->xev.type == ButtonPress) {
           if(self->p->xev.xbutton.button) {
                printf("%d,%d\n", self->p->xev.xbutton.x, self->p->xev.xbutton.y);
           }
       }
   }

   while(1) {
      displayResult(self, self->p->mainTable);
      usleep(DEFAULT_SLEEP_TIME_USEC);
      
      for(int i=0; i<self->p->playerCount; i++) {
         setCellsInTable(self->p->mainTable, self->p->tmpTable, self->p->players[i]);    
      }  
      swapTables(self->p->mainTable, self->p->tmpTable);

      while(XPending(self->p->display)) {
          XNextEvent(self->p->display, &self->p->xev);
          if(self->p->xev.type == KeyPress) {
              XCloseDisplay(self->p->display);
              return 0;
          }

          if(self->p->xev.type == ButtonPress) {
              if(self->p->xev.xbutton.button == 1) {

              }
          }

          if(self->p->xev.type == ButtonRelease) {
              if(self->p->xev.xbutton.button == 1) {

              }
          }
      }
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



static void initGraphics(Game *self)
{
    self->p->display = XOpenDisplay(NULL);
    if(self->p->display == NULL) {
       fprintf(stderr, "Can not open display\n");
       exit(1);
    }
    self->p->screen = DefaultScreen(self->p->display);

    initColorPallete(self->p->display, self->p->screen, &self->p->color);
    self->p->mainWindow = XCreateSimpleWindow(self->p->display, RootWindow(self->p->display, self->p->screen), 0, 0, 500 ,500, 0,self->p->color.black.pixel, self->p->color.black.pixel);
    XSelectInput(self->p->display, self->p->mainWindow, ExposureMask | KeyPressMask);
    XMapWindow(self->p->display, self->p->mainWindow);

    setFullScreen(self->p->display, self->p->mainWindow, self->p->xev);


    Window wid = DefaultRootWindow(self->p->display);
    XWindowAttributes xwAttr;
    XGetWindowAttributes(self->p->display, wid, &xwAttr);
    printf("%d %d", xwAttr.width, xwAttr.height);
    self->p->gameArea = XCreateSimpleWindow(self->p->display, self->p->mainWindow, 95, 95, xwAttr.width-205, xwAttr.height-205, 5,self->p->color.darkGray.pixel, self->p->color.dimGray.pixel);
    XSelectInput(self->p->display, self->p->mainWindow, ButtonPressMask | KeyPressMask);
    XMapWindow(self->p->display, self->p->gameArea);
    XGrabPointer(self->p->display, self->p->gameArea, False, ButtonPressMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
    XFlush(self->p->display);
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
   initGraphics(game);

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


