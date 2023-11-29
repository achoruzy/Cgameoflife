// Copyright (C) Arkadiusz Choruży

#ifndef CELL_H_
#define CELL_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int x;
    int y;
    bool isDead;
    int neighbours;
    int age;
} Cell;

typedef struct
{
    Cell *arrayPtr;
    int length;
} CellArray;

Cell *CreateCellArray(int size);
void InitializeMainCellArray();
CellArray GetMainCellArray();
void UpdateMainCellArray(Cell *ptr, int length);
void FreeMainCellArray();

#endif