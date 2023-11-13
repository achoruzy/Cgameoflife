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

void UpdateCellArray(Cell **cellArray, int *cellArrayLengthPtr, Vector2 mouseGridPos)
{
    // check for already exist and remove cell
    bool removed = false;
    for (int i = 0; i < *cellArrayLengthPtr; i++)
    {
        Cell currentCell = (*cellArray)[i];
        if (currentCell.x == (int)mouseGridPos.x && currentCell.y == (int)mouseGridPos.y)
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
            newArray[i] = (*cellArray)[i];
        }
        newArray[*cellArrayLengthPtr - 1] = (Cell){(int)mouseGridPos.x, (int)mouseGridPos.y, false, 0};

        free(*cellArray);
        *cellArray = newArray; // newArray not to free here as cellArray gots the address
    }
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
    int x, y;
    int count = 0;
    for (int i = 0; i < cellArrayLength; i++)
    {
        x = cellArray[i].x;
        y = cellArray[i].y;

        if (x == cell_x && y == cell_y)
            continue;

        if ((x == cell_x || x == cell_x - 1 || x == cell_x + 1) &&
            (y == cell_y || y == cell_y - 1 || y == cell_y + 1))
            count++;
    }
    return count;
}

int HandleExistingCells(Cell **survivedArrayPtr, Cell *cellArrayPtr, int cellArrayLength)
{
    int countSurvived = 0;
    for (int i = 0; i < cellArrayLength; i++)
    {
        Cell currentCell = cellArrayPtr[i];
        ValidateCellPos(currentCell.x, currentCell.y);
        currentCell.neighbours = CellNeighborsQty(currentCell.x, currentCell.y, cellArrayPtr, cellArrayLength);
        bool isSurvived = isToLive(currentCell.neighbours);

        if (isToLive(currentCell.neighbours)) // if obey then it stays and appends to new array
        {
            currentCell.isDead = true;
            (*survivedArrayPtr)[countSurvived] = currentCell;

            countSurvived++;
        }
    }
    return countSurvived;
}

int SpawnNewCells(Cell **spawnedArrayPtr, Cell *cellArrayPtr, int cellArrayLength)
{
    int countSpawned = 0;

    for (int i = 0; i < cellArrayLength; i++) // check around existing only
    {
        // TODO: handle grid edge
        Cell currentCell = cellArrayPtr[i];
        ValidateCellPos(currentCell.x, currentCell.y);
        for (int x = currentCell.x - 1; x <= currentCell.x + 1; x++)
        {
            for (int y = currentCell.y - 1; y <= currentCell.y + 1; y++)
            {
                if (IsCellEmpty(cellArrayPtr, cellArrayLength, x, y) && IsCellEmpty(*spawnedArrayPtr, countSpawned, x, y))
                {
                    int emptyCellNeighbors = CellNeighborsQty(x, y, cellArrayPtr, cellArrayLength);
                    if (isToRevive(emptyCellNeighbors))
                    {
                        Cell spawnedCell = {x, y, false, emptyCellNeighbors};
                        (*spawnedArrayPtr)[countSpawned] = spawnedCell;
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
    Cell *resultArrPtr = CellArray(len1 + len2);
    if (resultArrPtr == NULL)
    {
        free(arr1Ptr);
        free(arr2Ptr);
        puts("Error: (re)allocating memory resultArrayPtr");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < len1; i++)
        resultArrPtr[i] = arr1Ptr[i];
    for (int i = 0; i < len2; i++)
        resultArrPtr[len1 + i] = arr2Ptr[i];
    return resultArrPtr;
}

void ValidateCellPos(int x, int y)
{
    int min = -50;
    int max = 50;
    if (x < min || x > max || y < min || y > max)
    {
        printf("Error: Cell has coordinates out of grid: %i, %i\n", x, y);
        exit(EXIT_FAILURE);
    }
}

void SurroundedCellsPositions(Vector2 **surroundedPtr, Cell cell, int gridSize)
{
    // O12
    // 3x4
    // 567

    int min = 0;
    int max = gridSize - 1;
    *surroundedPtr = (Vector2 *)malloc(8 * sizeof(Vector2));

    if (cell.x < min || cell.x > max || cell.y < min || cell.y > max)
    {
        printf("Error: Cell has coordinates out of grid: %i, %i\n", cell.x, cell.y);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            if (x == cell.x && y == cell.y)
                continue;

            if (x < min || x > max || y < min || y > max)
                continue;
            int newX = x;
            int newY = y;

            (*surroundedPtr)[i].x = newX;
            (*surroundedPtr)[i].y = newY;
            i++;
        }
    }

    if (cell.x == 0)
    {
        (*surroundedPtr)[0].x = max;
        (*surroundedPtr)[3].x = max;
        (*surroundedPtr)[5].x = max;
    }
    else if (cell.x == max)
    {
        (*surroundedPtr)[2].x = min;
        (*surroundedPtr)[4].x = min;
        (*surroundedPtr)[7].x = min;
    }

    if (cell.y == 0)
    {
        (*surroundedPtr)[0].y = max;
        (*surroundedPtr)[1].y = max;
        (*surroundedPtr)[2].y = max;
    }
    else if (cell.y == max)
    {
        (*surroundedPtr)[5].y = min;
        (*surroundedPtr)[6].y = min;
        (*surroundedPtr)[7].y = min;
    }
}