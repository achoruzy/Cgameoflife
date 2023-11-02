// Copyright (C) Arkadiusz Choruży

#ifndef CELL_UTILS_H_
#define CELL_UTILS_H_

#include "cell.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Function for creting CellArray struct variable
Cell *CellArray(int size);

// Updates main CellArray on user input
Cell *UpdateCellArray(Cell *cellArray, int *cellArrayLengthPtr, Vector2 mouseGridPos);

void UpdateOne(Cell *arrayPtr, int i, int x, int y, bool isDead, int neighbors);

bool IsCellEmpty(Cell *array, int lenght, int x, int y);

// Calculates number of cell neighbors
int CellNeighborsQty(int cell_x, int cell_y, Cell *cellArray, int cellArrayLengthPtr);

#endif