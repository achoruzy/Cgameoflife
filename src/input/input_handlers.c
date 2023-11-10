// Copyright (C) Arkadiusz Choruży

#include "input_handlers.h"

void HooverGridCell(int x, int y, float spacing, Color color)
{
    DrawRectangleLines(x * spacing, y * spacing, spacing, spacing, color);
}