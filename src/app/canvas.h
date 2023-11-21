// Copyright (C) Arkadiusz Choruży

#ifndef CANVAS_H_
#define CANVAS_H_

#include "window.h"
#include "../input/mouse.h"
#include "../logic/grid.h"
#include "../logic/cell.h"
#include "../draw/draw_grid.h"
#include "../draw/draw_cell.h"
#include "../input/input_handlers.h"
#include <raylib.h>
#include <rlgl.h>

void DrawCanvas(Cell *cellArrayPtr, int cellArrayLength, bool isPause);

#endif