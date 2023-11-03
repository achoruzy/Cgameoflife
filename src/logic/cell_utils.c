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
    // for (int i = 0; i < *cellArrayLengthPtr; i++)
    // {
    //     Cell *current = cellArray + i;
    //     if (current->x == (int)mouseGridPos.x && current->y == (int)mouseGridPos.y)
    //     {
    //         // TODO: remove works now as UNDO
    //         (*cellArrayLengthPtr)--;
    //         removed = true;
    //     }
    // }
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

void UpdateOne(Cell *arrayPtr, int i, int x, int y, bool isDead, int neighbors)
{
    arrayPtr[i].x = x;
    arrayPtr[i].y = y;
    arrayPtr[i].isDead = isDead;
    arrayPtr[i].neighbours = neighbors;
}

bool IsCellEmpty(Cell *arrayPtr, int lenght, int x, int y)
{
    for (int i = 0; i < lenght; i++)
    {
        if (arrayPtr[i].x == x && arrayPtr[i].y == y)
            return false;
    }
    return true;
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

    // TODO: handle grid edge
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

int HandleExistingCells(Cell *cellArrayPtr, int cellArrayLength)
{
    Cell *survivedArrayPtr = CellArray(cellArrayLength);
    int countSurvived = 0;

    for (int i = 0; i < cellArrayLength; i++)
    {
        Cell *currentPtr = &cellArrayPtr[i];
        int cellNeighbors = CellNeighborsQty(currentPtr->x, currentPtr->y, cellArrayPtr, cellArrayLength);
        bool isCellObeyRules = TryObeyRules(currentPtr, cellNeighbors);

        if (isCellObeyRules) // if obey then it stays and appends to new array
        {
            survivedArrayPtr[countSurvived] = *currentPtr;
            countSurvived++;
        }
    }
    free(cellArrayPtr);
    cellArrayPtr = survivedArrayPtr;
    return countSurvived;
}

int SpawnNewCells(Cell *spawnedArrayPtr, Cell *cellArrayPtr, int cellArrayLength)
{
    int countSpawned = 0;

    for (int i = 0; i < cellArrayLength; i++) // check around existing only
    {
        // TODO: handle grid edge
        Cell *currentPtr = &cellArrayPtr[i];
        for (int x = currentPtr->x - 1; x <= currentPtr->x + 1; x++)
        {
            for (int y = currentPtr->y - 1; y <= currentPtr->y + 1; y++)
            {
                // don't check current -> middle one in 3x3 around grid
                if (x == 0 && y == 0)
                    continue;

                // check empty cell if may live
                if (IsCellEmpty(cellArrayPtr, cellArrayLength, x, y))
                {
                    int emptyCellNeighbors = CellNeighborsQty(x, y, cellArrayPtr, cellArrayLength);
                    if (isToRevive(emptyCellNeighbors))
                    {
                        spawnedArrayPtr[countSpawned] = *currentPtr;
                        countSpawned++;
                    }
                }
            }
        }
    }
    return countSpawned;
}

Cell *ConcatenateCellArrays(Cell *arr1Ptr, int len1, Cell *arr2Ptr, int len2)
{
    Cell *resultArr = CellArray(len1 + len2);
    int i = 0;
    for (i; i < len1; i++)
    {
        resultArr[i] = arr1Ptr[i];
    }
    for (i; i < len1 + len2; i++)
    {
        resultArr[i] = arr1Ptr[i - len1];
    }
    return resultArr;
}