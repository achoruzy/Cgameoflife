#ifndef LOGIC
#define LOGIC

// Cell struct with x, y, isDead
typedef struct Cell {
    int x;
    int y;
    bool isDead;
    int neighbours;
} Cell;

Cell* CellArray(int size){}

#endif