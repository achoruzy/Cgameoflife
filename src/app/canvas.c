// Copyright (C) Arkadiusz Choruży

#include "canvas.h"

static Color GetCellColor(int age);

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
                Color color = GetCellColor(cellArrayPtr[i].age);
                DrawCell(cellArrayPtr[i].x, cellArrayPtr[i].y, grid.spacing, color);
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

static Color GetCellColor(int age)
{
    int c = 20 * age;
    int r = Clamp(50 + c, 50, 255);
    int g = Clamp(255 - c, 50, 255);
    int b = Clamp(c, 70, 255);
    return (Color){r, g, b, 255};
}