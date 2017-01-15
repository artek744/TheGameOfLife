#ifndef CELL_FILE
#define CELL_FILE

typedef enum 
{
   NOCOLOR, 
   RED, 
   GREEN, 
   YELLOW, 
   BLUE
} Color;

typedef struct Cell
{
   int x;
   int y;
   Color color;
} Cell;

Cell createCell(Color color, int x, int y);


#endif

