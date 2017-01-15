#include <stdlib.h>

#include "../headers/cell.h"


Cell *createCell(Color color, int x, int y)
{
   Cell *cell = malloc(sizeof(Cell));
   cell->color = color;
   cell->x = x;
   cell->y = y;

   return cell;
}

void destroyCell(Cell *cell)
{
   free(cell);
}
