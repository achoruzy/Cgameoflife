// Copyright (C) Arkadiusz Choruży

#ifndef LOGIC_H_
#define LOGIC_H_

// Cell struct with x, y, isDead
typedef struct Cell {
    int x;
    int y;
    bool isDead;
    int neighbours;
} Cell;

// Function for creting CellArray struct variable
Cell* CellArray(int size);

#endif