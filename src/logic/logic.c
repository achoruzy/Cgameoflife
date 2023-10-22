#include <stdbool.h>

// Cell struct with x, y, isDead

typedef struct Cell {
    int x;
    int y;
    bool isDead;
    int neighbours;
} Cell;

Cell* CellArray(int size)
{
    Cell* cellPtr;
    cellPtr = (Cell*)calloc(size, sizeof(Cell));
    cellPtr->x = (int)malloc(sizeof(int));
    cellPtr->y = (int)malloc(sizeof(int));
    cellPtr->isDead = (bool)malloc(sizeof(bool));
    cellPtr->y = (int)malloc(sizeof(int));
    return cellPtr;
}

// check neighbourhood -> calculate num of neighbours -> decide on rules