// Copyright (C) Arkadiusz Choruży


#include "cell.h"


Cell* CellArray(int size)
{
    Cell* cellPtr;
    cellPtr = (Cell*)calloc(size, sizeof(Cell));
    return cellPtr;
}

// check neighbourhood -> calculate num of neighbours -> decide on rules