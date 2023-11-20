// Copyright (C) Arkadiusz Choruży

#include "mouse.h"

static MouseInfo mouseInfo;

void UpdateMouseInfo(Camera2D mainCamera, float spacing)
{
    mouseInfo.ScreenPos = GetMousePosition();
    mouseInfo.WorldPos = GetScreenToWorld2D(mouseInfo.ScreenPos, mainCamera);
    mouseInfo.GridPos = WorldToGrid(mouseInfo.WorldPos, spacing);
}

MouseInfo GetMouseInfo() { return mouseInfo; }