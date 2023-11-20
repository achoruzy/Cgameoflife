// Copyright (C) Arkadiusz Choruży

#ifndef MOUSE_H_
#define MOUSE_H_

#include <raylib.h>
#include "../logic/grid_utils.h"

typedef struct
{
	Vector2 ScreenPos;
	Vector2 WorldPos;
	Vector2 GridPos;
} MouseInfo;

void UpdateMouseInfo(Camera2D mainCamera, float spacing);
MouseInfo GetMouseInfo();

#endif