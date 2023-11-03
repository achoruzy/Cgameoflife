// Copyright (C) Arkadiusz Choruży

#ifndef CELL_UTILS_H_
#define CELL_UTILS_H_

#include "cell.h"
#include "convay_rules.h"

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

int HandleExistingCells(Cell *cellArrayPtr, int cellArrayLength);

int SpawnNewCells(Cell *spawnedArrayPtr, Cell *cellArrayPtr, int cellArrayLength);

Cell *ConcatenateCellArrays(Cell *arr1, int len1, Cell *arr2, int len2);

#endif