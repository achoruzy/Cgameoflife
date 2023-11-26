// Copyright (C) Arkadiusz Choruży

#include "cell.h"

static CellArray cellArray;

Cell *CreateCellArray(int size)
{
    Cell *cellPtr = calloc(size, sizeof(Cell));
    if (cellPtr == NULL)
    {
        printf("Error: Cell pointers occured NULL");
        exit(EXIT_FAILURE);
    }
    return cellPtr;
}

void InitializeMainCellArray()
{
    cellArray.arrayPtr = CreateCellArray(0);
    cellArray.length = 0;
}

CellArray GetMainCellArray()
{
    return cellArray;
}

void UpdateMainCellArray(Cell *ptr, int length)
{
    cellArray.arrayPtr = ptr;
    cellArray.length = length;
}

void FreeMainCellArray()
{
    free(cellArray.arrayPtr);
}