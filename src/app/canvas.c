// Copyright (C) Arkadiusz Choruży

#include "canvas.h"

static Shader postprocess;
static RenderTexture2D target;

void InitializeCanvas()
{
    postprocess = LoadShader(0, TextFormat("shaders/bloom.fs"));
    target = LoadRenderTexture(GetWindow().width, GetWindow().height);
}

void DeinitializeCanvas()
{
    UnloadShader(postprocess);
}

void DrawCanvas()
{
    Grid grid = GetGrid();
    CellArray cellArray = GetMainCellArray();
    Cell *cellArrayPtr = cellArray.arrayPtr;
    int cellArrayLength = cellArray.length;

    BeginTextureMode(target);
    ClearBackground(BLANK);
    {
        BeginMode2D(GetWindow().camera);
        {
            for (int i = 0; i < cellArrayLength; i++)
            {
                DrawCell(cellArrayPtr[i].x, cellArrayPtr[i].y, grid.spacing, WHITE);
            }
        }
        EndMode2D();
    }
    EndTextureMode();

    BeginDrawing();
    ClearBackground(GetWindow().bgColor);
    {
        BeginMode2D(GetWindow().camera);
        if (grid.isActive)
            DrawUnifiedGrid2D(grid.size, grid.spacing, grid.color, grid.lineThickness, true);
        HooverGridCell(GetMouseInfo().GridPos.x, GetMouseInfo().GridPos.y, grid.spacing, LIGHTGRAY);
        EndMode2D();
    }

    BeginShaderMode(postprocess);
    DrawTextureRec(target.texture, (Rectangle){0, 0, GetWindow().width, -GetWindow().height}, (Vector2){0, 0}, WHITE);
    EndShaderMode();

    // DRAW UI
    BeginMode2D(GetWindow().camera);
    {
        Color color = GetInputFlags().isPause ? RED : GREEN;
        Vector2 screenPos = GetScreenToWorld2D((Vector2){GetWindow().width - 50, GetWindow().height - 50}, GetWindow().camera);
        DrawCircle(screenPos.x, screenPos.y, 10.f, color);
    }
    EndMode2D();
    DrawFPS(10, 10);
    EndDrawing();
}