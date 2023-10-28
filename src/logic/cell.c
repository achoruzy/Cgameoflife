// Copyright (C) Arkadiusz Choruży

#include "cell.h"

Cell *CellArray(int size)
{
    Cell *cellPtr;
    cellPtr = (Cell *)calloc(size, sizeof(Cell));
    return cellPtr;
}

int CellNeighborsQty(int cell_x, int cell_y, Cell *cellArray, int cellArrayLength)
{
    /* cases
    N -> x, y-1
    S -> x, y+1
    W -> x-1, y
    E -> x+1, y
    NW -> x-1, y-1
    NE -> x+1, y-1
    SW -> x-1, y+1
    SE -> x+1, y+1
    */
    int count = 0;
    for (int i = 0; i < cellArrayLength; i++)
    {
        int x = cellArray[i].x;
        int y = cellArray[i].y;

        if (x == cell_x && y == cell_y)
            continue;

        if (x == cell_x || x == cell_x - 1 || x == cell_x + 1)
        {
            if (y == cell_y || y == cell_y - 1 || y == cell_y + 1)
                count++;
        }
    }
    return count;
}