// Copyright (C) Arkadiusz Choruży

#include "canvas.h"

void DrawCanvas(Cell *cellArrayPtr, int cellArrayLength, bool isPause)
{
    Grid grid = GetGrid();

    BeginDrawing();
    BeginMode2D(GetWindow().camera);
    ClearBackground(GetWindow().bgColor);

    if (grid.isActive)
        DrawUnifiedGrid2D(grid.size, grid.spacing, grid.color, grid.lineThickness, true);
    HooverGridCell(GetMouseInfo().GridPos.x, GetMouseInfo().GridPos.y, grid.spacing, LIGHTGRAY);

    // DRAW EXISTING CELLS
    for (int i = 0; i < cellArrayLength; i++)
    {
        DrawCell(cellArrayPtr[i].x, cellArrayPtr[i].y, grid.spacing, WHITE);
    }
    // POSTPROCESS CANVAS

    // DRAW UI
    {
        Color color = isPause ? RED : GREEN;
        Vector2 screenPos = GetScreenToWorld2D((Vector2){GetWindow().width - 50, GetWindow().height - 50}, GetWindow().camera);
        DrawCircle(screenPos.x, screenPos.y, 10.f, color);
    }

    EndMode2D();
    DrawFPS(10, 10);
    EndDrawing();
}