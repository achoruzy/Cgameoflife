// Copyright (C) Arkadiusz Choruży


#ifndef CELLS_H_
#define CELLS_H_

#include "../logic/logic.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>

// Updates main CellArray on user input
Cell* UpdateCellArray(Cell* cellArray, int* cellArrayLengthPtr, Vector2 mouseGridPos);

#endif