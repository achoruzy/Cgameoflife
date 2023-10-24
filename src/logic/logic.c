// Copyright (C) Arkadiusz Choruży

#include <stdbool.h>
#include "logic.h"

#include <stdlib.h>

Cell* CellArray(int size)
{
    Cell* cellPtr;
    cellPtr = (Cell*)calloc(size, sizeof(Cell));
    return cellPtr;
}

// check neighbourhood -> calculate num of neighbours -> decide on rules