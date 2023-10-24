// Copyright (C) Arkadiusz Choruży


#include "cells.h"
#include "../logic/logic.h"
#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>


Cell* UpdateCellArray(Cell* cellArray, int* cellArrayLengthPtr, Vector2 mouseGridPos)
{
    // check for already exist and remove cell
    bool removed = false;

    for (int i = 0; i < *cellArrayLengthPtr; i++)
    {
        Cell* current = cellArray + i;
        if (current->x == (int)mouseGridPos.x && current->y == (int)mouseGridPos.y)
        {
            // remove
            (*cellArrayLengthPtr)--;
            removed = true;
        }
    }
    // append
    if (!removed)
    {
        (*cellArrayLengthPtr)++;
        Cell* newArray = CellArray(*cellArrayLengthPtr);
        
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


