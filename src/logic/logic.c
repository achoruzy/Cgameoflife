#include <stdbool.h>
#include <stdlib.h>
#include "../logic/logic.h"

Cell* CellArray(int size)
{
    Cell* cellPtr;
    cellPtr = (Cell*)calloc(size, sizeof(Cell));
    return cellPtr;
}

// check neighbourhood -> calculate num of neighbours -> decide on rules