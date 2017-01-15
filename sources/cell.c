#include <stdlib.h>

#include "../headers/cell.h"


Cell createCell(Color color, int x, int y)
{
   Cell cell;
   cell.color = color;
   cell.x = x;
   cell.y = y;

   return cell;
}

