// Copyright (C) Arkadiusz Choruży

#include "automata.h"

void RunAutomata(Cell **cellArrayPtr, int *cellArrayLength)
{
    Cell *survivedArrayPtr = CellArray(*cellArrayLength);
    int survivedCount = HandleExistingCells(&survivedArrayPtr, *cellArrayPtr, *cellArrayLength);
    Cell *spawnedArrayPtr = CellArray(survivedCount * 8);
    int spawnedCount = SpawnNewCells(&spawnedArrayPtr, *cellArrayPtr, *cellArrayLength);

    free(*cellArrayPtr);
    if (survivedCount > 0 && spawnedCount > 0)
    {
        Cell *drawArrayPtr = ConcatenateCellArrays(survivedArrayPtr, survivedCount, spawnedArrayPtr, spawnedCount);
        free(survivedArrayPtr);
        free(spawnedArrayPtr);
        *cellArrayPtr = drawArrayPtr;
        *cellArrayLength = survivedCount + spawnedCount;
    }
    else if (survivedCount > 0 && spawnedCount <= 0)
    {
        free(spawnedArrayPtr);
        *cellArrayPtr = survivedArrayPtr;
        *cellArrayLength = survivedCount;
    }
    else if (survivedCount <= 0 && spawnedCount > 0)
    {
        free(survivedArrayPtr);
        *cellArrayPtr = spawnedArrayPtr;
        *cellArrayLength = spawnedCount;
    }
}