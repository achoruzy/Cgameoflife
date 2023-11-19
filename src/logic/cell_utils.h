// Copyright (C) Arkadiusz Choruży

#ifndef CELL_UTILS_H_
#define CELL_UTILS_H_

#include "cell.h"
#include "rules.h"

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// Function for creting CellArray struct variable
Cell *CellArray(int size);

// Updates given cell array on user input with given grid position, spawns new or deletes existing one.
void UpdateCellArray(Cell **cellArray, int *cellArrayLengthPtr, Vector2 gridPos);

// Checks if cell in given xy position is empty
bool IsCellEmpty(Cell *array, int arrLenght, int x, int y);

// Returns number of living cell neighbors around given xy position.
int CellNeighborsQty(int cell_x, int cell_y, Cell *cellArray, int cellArrayLengthPtr);

// Fills given array of cells with survived cells. Returns number of survivals.
int HandleExistingCells(Cell **survivedArrayPtr, Cell *cellArrayPtr, int cellArrayLength);

// Fills given array of cells with spawned new cells. Returns number of spawns.
int SpawnNewCells(Cell **spawnedArrayPtr, Cell *cellArrayPtr, int cellArrayLength);

// Creates new array of cells from two given arrays.
Cell *ConcatenateCellArrays(Cell *arr1, int len1, Cell *arr2, int len2);

// Checks given cell position for proper placing in active grid.
static void ValidateCellPos(int x, int y);

#endif