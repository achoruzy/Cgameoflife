// Copyright (C) Arkadiusz Choruży


#include "draw_grid.h"


void DrawUnifiedGrid2D(int size, float spacing, Color color, float thickness, bool centered)
{
    float gridSize = size * spacing;
    float halfGridSize = gridSize / 2;

    float gridTranslation = 0;
    if (centered) gridTranslation = halfGridSize;

    rlBegin(RL_LINES);
    rlSetLineWidth(thickness);
    rlColor4f(color.r, color.g, color.b, color.a);

    float ixspacing;
    for (int i = 0; i <= size; i++) 
    {
        ixspacing = i * spacing - gridTranslation;
        rlVertex2f(-gridTranslation, ixspacing);
        rlVertex2f(gridSize-gridTranslation, ixspacing);

        rlVertex2f(ixspacing, -gridTranslation);
        rlVertex2f(ixspacing, gridSize-gridTranslation);
    }
    rlEnd();
}