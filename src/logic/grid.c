// Copyright (C) Arkadiusz Choruży

#include "grid.h"

static Grid grid;

void InitializeGrid()
{
    grid.size = 100;
    grid.spacing = 10;
    grid.lineThickness = .2f;
    grid.color = (Color){100, 100, 100, 200};
    grid.isActive = true;
}

void SetGridActive(bool state) { grid.isActive = state; }