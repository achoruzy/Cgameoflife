// Copyright (C) Arkadiusz Choruży

#ifndef GRID_H_
#define GRID_H_

#include <raylib.h>
#include "../logic/grid_utils.h"

typedef struct {
    int size;
	int spacing;
} Grid;

extern Grid GRID;

#endif