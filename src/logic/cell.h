// Copyright (C) Arkadiusz Choruży

#ifndef LOGIC_H_
#define LOGIC_H_

#include <stdbool.h>
#include <stdlib.h>

// Cell struct with x, y, isDead
typedef struct {
    int x;
    int y;
    bool isDead;
    int neighbours;
} Cell;

// Function for creting CellArray struct variable
Cell* CellArray(int size);

#endif