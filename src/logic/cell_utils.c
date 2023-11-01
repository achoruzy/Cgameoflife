// Copyright (C) Arkadiusz Choruży

#include "cell_utils.h"

Cell *CellArray(int size)
{
    Cell *cellPtr = (Cell *)calloc(size, sizeof(Cell));
    if (cellPtr == NULL)
    {
        printf("Error: Cell pointers occured NULL");
        exit(EXIT_FAILURE);
    }
    return cellPtr;
}

Cell *UpdateCellArray(Cell *cellArray, int *cellArrayLengthPtr, Vector2 mouseGridPos)
{
    // check for already exist and remove cell
    bool removed = false;

    for (int i = 0; i < *cellArrayLengthPtr; i++)
    {
        Cell *current = cellArray + i;
        if (current->x == (int)mouseGridPos.x && current->y == (int)mouseGridPos.y)
        {
            // TODO: remove works now as UNDO
            (*cellArrayLengthPtr)--;
            removed = true;
        }
    }
    // append
    if (!removed)
    {
        (*cellArrayLengthPtr)++;
        Cell *newArray = CellArray(*cellArrayLengthPtr);

        for (int i = 0; i < *cellArrayLengthPtr - 1; i++)
        {
            newArray[i] = cellArray[i];
        }
        newArray[*cellArrayLengthPtr - 1] = (Cell){mouseGridPos.x, mouseGridPos.y, false, 0};

        free(cellArray);
        cellArray = newArray; // newArray not to free here as cellArray gots the address
    }
    return cellArray;
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

    // TODO: grid end handling
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