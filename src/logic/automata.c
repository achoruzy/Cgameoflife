// Copyright (C) Arkadiusz Choruży

#include "automata.h"

void RunAutomata()
{
    CellArray cellArray = GetMainCellArray();
    Cell *cellArrayPtr = cellArray.arrayPtr;
    int cellArrayLength = cellArray.length;

    Cell *survivedArrayPtr = CreateCellArray(cellArrayLength);
    int survivedCount = HandleExistingCells(&survivedArrayPtr, cellArrayPtr, cellArrayLength);
    Cell *spawnedArrayPtr = CreateCellArray(survivedCount * 8);
    int spawnedCount = SpawnNewCells(&spawnedArrayPtr, cellArrayPtr, cellArrayLength);

    FreeMainCellArray();
    if (survivedCount > 0 && spawnedCount > 0)
    {
        Cell *drawArrayPtr = ConcatenateCellArrays(survivedArrayPtr, survivedCount, spawnedArrayPtr, spawnedCount);
        free(survivedArrayPtr);
        free(spawnedArrayPtr);
        UpdateMainCellArray(drawArrayPtr, survivedCount + spawnedCount);
    }
    else if (survivedCount > 0 && spawnedCount <= 0)
    {
        free(spawnedArrayPtr);
        UpdateMainCellArray(survivedArrayPtr, survivedCount);
    }
    else if (survivedCount <= 0 && spawnedCount > 0)
    {
        free(survivedArrayPtr);
        UpdateMainCellArray(spawnedArrayPtr, spawnedCount);
    }
}