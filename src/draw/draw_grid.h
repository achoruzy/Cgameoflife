// Copyright (C) Arkadiusz Choruży

#ifndef DRAW_GRID_H_
#define DRAW_GRID_H_

#include <stdbool.h>
#include <raylib.h>
#include <rlgl.h>

// Draw a unified 2D grid. 
void DrawUnifiedGrid2D(int size, float spacing, Color color, float thickness, bool centered);

#endif