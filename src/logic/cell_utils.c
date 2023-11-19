// Copyright (C) Arkadiusz Choruży

#include "cell_utils.h"

Cell *CellArray(int size)
{
    Cell *cellPtr = calloc(size, sizeof(Cell));
    if (cellPtr == NULL)
    {
        printf("Error: Cell pointers occured NULL");
        exit(EXIT_FAILURE);
    }
    return cellPtr;
}

void UpdateCellArray(Cell **cellArray, int *cellArrayLengthPtr, Vector2 mouseGridPos)
{
    // check for already exist and remove cell if exists
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
    // append new cell
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
        *cellArray = newArray;
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

int CellNeighborsQty(int x, int y, Cell *cellArray, int cellArrayLength)
{
    int min = -50;
    int max = 49;
    int current_x, current_y;
    int x_left, x_right, y_top, y_bottom;

    x_left = x == min ? max : x - 1;
    x_right = x == max ? min : x + 1;
    y_bottom = y == min ? max : y - 1;
    y_top = y == max ? min : y + 1;

    int count = 0;
    for (int i = 0; i < cellArrayLength; i++)
    {
        current_x = cellArray[i].x;
        current_y = cellArray[i].y;

        if (current_x == x && current_y == y)
            continue;

        if ((current_x == x_left || current_x == x || current_x == x_right) &&
            (current_y == y_top || current_y == y || current_y == y_bottom))

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

    int min = -50;
    int max = 49;
    int current_x, current_y;
    int x_left, x_right, y_top, y_bottom;

    for (int i = 0; i < cellArrayLength; i++) // check around existing only
    {
        Cell currentCell = cellArrayPtr[i];
        current_x = currentCell.x;
        current_y = currentCell.y;
        ValidateCellPos(current_x, current_y);

        x_left = current_x == min ? max : current_x - 1;
        x_right = current_x == max ? min : current_x + 1;
        y_bottom = current_y == min ? max : current_y - 1;
        y_top = current_y == max ? min : current_y + 1;

        int x_arr[] = {x_left, current_x, x_right};
        int y_arr[] = {y_top, current_y, y_bottom};

        for (int m = 0; m < 3; m++)
        {
            int x = x_arr[m];
            for (int n = 0; n < 3; n++)
            {
                int y = y_arr[n];
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
    for (int i = 0; i < len1; i++)
        resultArrPtr[i] = arr1Ptr[i];
    for (int i = 0; i < len2; i++)
        resultArrPtr[len1 + i] = arr2Ptr[i];
    return resultArrPtr;
}

static void ValidateCellPos(int x, int y)
{
    int min = -50;
    int max = 49;
    if (x < min || x > max || y < min || y > max)
    {
        printf("Error: Cell has coordinates out of grid: %i, %i\n", x, y);
        exit(EXIT_FAILURE);
    }
}