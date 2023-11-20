// Copyright (C) Arkadiusz Choruży

#ifndef GRID_H_
#define GRID_H_

#include <raylib.h>
#include "../logic/grid_utils.h"
#include <stdbool.h>

typedef struct
{
    int size;
    int spacing;
    float lineThickness;
    Color color;
    bool isActive;
} Grid;

void InitializeGrid();
Grid GetGrid();
void SetGridActive(bool state);

#endif