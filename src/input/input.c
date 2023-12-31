// Copyright (C) Arkadiusz Choruży

#include "input.h"

static InputFlags inputFlags;

void InitializeInput()
{
    inputFlags.isPause = true;
}

InputFlags GetInputFlags() { return inputFlags; }

void ProcessInput()
{
    UpdateMouseInfo(GetWindow().camera, GetGrid().spacing);
    if (IsKeyPressed(KEY_F1))
        ProcessToggleFullscreen();
    if (IsKeyPressed(KEY_F2))
        ProcessToggleGridActive();
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        ProcessCameraMove();
    if (IsKeyPressed(KEY_SPACE))
        ProcessAutomataPause();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        ProcessUpdateCellArray();
}

static void ProcessToggleFullscreen() // TODO: return to window is buggy
{
    if (IsWindowFullscreen())
        SetWindowSize(GetWindow().width, GetWindow().height);
    else
    {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    }
    ToggleFullscreen();
}

static void ProcessToggleGridActive()
{
    Grid grid = GetGrid();
    SetGridActive(!grid.isActive);
}

static void ProcessCameraMove()
{
    Grid grid = GetGrid();
    float gridHalfWidth = grid.size * grid.spacing / 2;
    UpdateCameraOffset(gridHalfWidth, gridHalfWidth);
}

static void ProcessAutomataPause()
{
    inputFlags.isPause = !inputFlags.isPause;
}

static void ProcessUpdateCellArray()
{
    CellArray cellArray = GetMainCellArray();
    Cell *cellArrayPtr = cellArray.arrayPtr;
    int cellArrayLength = cellArray.length;
    UpdateCellArray(cellArray, GetMouseInfo().GridPos);
}