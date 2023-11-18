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
void UpdateCellArray(Cell **cellArray, int *cellArrayLengthPtr, Vector2 mouseGridPos);

bool IsCellEmpty(Cell *array, int lenght, int x, int y);

// Calculates number of cell neighbors
int CellNeighborsQty(int cell_x, int cell_y, Cell *cellArray, int cellArrayLengthPtr);

int HandleExistingCells(Cell **survivedArrayPtr, Cell *cellArrayPtr, int cellArrayLength);

int SpawnNewCells(Cell **spawnedArrayPtr, Cell *cellArrayPtr, int cellArrayLength);

Cell *ConcatenateCellArrays(Cell *arr1, int len1, Cell *arr2, int len2);

static void ValidateCellPos(int x, int y);

#endif