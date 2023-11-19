// Copyright (C) Arkadiusz Choruży

#ifndef GRID_UTILS_H_
#define GRID_UTILS_H_

#include <raylib.h>
#include <math.h>

// Calculates grid position from world position.
Vector2 WorldToGrid(Vector2 worldPos, float gridSpacing);

#endif