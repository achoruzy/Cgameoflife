// Copyright (C) Arkadiusz Choruży

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/logic/cell.h"
#include "./src/logic/cell_utils.h"
#include "./src/logic/convay_rules.h"
#include "./src/logic/grid.h"
#include "./src/draw/draw_grid.h"
#include "./src/draw/draw_cell.h"

int main()
{
	const int screenWidth = 800;
	const int screenHeight = 600;

	Color bgColor = {21, 30, 39, 255};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(screenWidth, screenHeight, "C Game of Life");
	SetWindowMinSize(screenWidth, screenHeight);
	SetTargetFPS(60);

	Camera2D mainCamera = {0};
	mainCamera.target = (Vector2){-screenWidth / 2, -screenHeight / 2}; // camera pivot, left top
	mainCamera.zoom = 1.f;

	// Runtime config
	float spacing = 10;
	int gridSize = 100;
	Color gridColor = {100, 100, 100, 200};
	float gridThickness = .2f;
	float screenMargin = 25.f;
	float gridHalfWidth = gridSize * spacing / 2;

	// Logic
	int cellArrayLength = 0;
	Cell *cellArrayPtr = CellArray(cellArrayLength);

	// UI flags
	bool isPause = true;

	// Time
	double logicCooldown = 0;

	while (!WindowShouldClose())
	{
		Vector2 mouseScreenPos = GetMousePosition();
		Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, mainCamera);
		Vector2 mouseGridPos = WorldToGrid(mouseWorldPos, spacing);

		int monitor = GetCurrentMonitor();
		if (IsKeyPressed(KEY_F1))
		{
			if (IsWindowFullscreen())
				SetWindowSize(screenWidth, screenHeight);
			else
				SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
			ToggleFullscreen();
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			mainCamera.offset = Vector2Clamp(
				Vector2Add(mainCamera.offset, GetMouseDelta()),
				(Vector2){-gridHalfWidth + (screenWidth / 2) - screenMargin, -gridHalfWidth + (screenHeight / 2) - screenMargin},
				(Vector2){gridHalfWidth - (screenWidth / 2) + screenMargin, gridHalfWidth - (screenHeight / 2) + screenMargin}); // TODO: limit to grid size
		}
		if (IsKeyPressed(KEY_SPACE))
			isPause = !isPause;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // can add or remove at least one at a time
			UpdateCellArray(&cellArrayPtr, &cellArrayLength, mouseGridPos);

		// Time management
		logicCooldown += GetFrameTime();

		// MAIN LOGIC
		if (!isPause && logicCooldown > 0.2)
		{
			logicCooldown = 0;

			Cell *survivedArrayPtr = CellArray(cellArrayLength);
			int survivedCount = HandleExistingCells(&survivedArrayPtr, cellArrayPtr, cellArrayLength);
			Cell *spawnedArrayPtr = CellArray(survivedCount);
			int spawnedCount = SpawnNewCells(&spawnedArrayPtr, cellArrayPtr, cellArrayLength);

			if (survivedCount > 0 && spawnedCount > 0)
			{
				Cell *drawArrayPtr = ConcatenateCellArrays(survivedArrayPtr, survivedCount, spawnedArrayPtr, spawnedCount);
				free(cellArrayPtr);
				free(survivedArrayPtr);
				free(spawnedArrayPtr);
				cellArrayPtr = drawArrayPtr;
				cellArrayLength = survivedCount + spawnedCount;
			}
			else if (survivedCount > 0 && spawnedCount <= 0)
			{
				free(cellArrayPtr);
				free(spawnedArrayPtr);
				cellArrayPtr = survivedArrayPtr;
				cellArrayLength = survivedCount;
			}
			else if (survivedCount <= 0 && spawnedCount > 0)
			{
				free(cellArrayPtr);
				free(survivedArrayPtr);
				cellArrayPtr = spawnedArrayPtr;
				cellArrayLength = spawnedCount;
			}
		}

		// DRAW CANVAS
		BeginDrawing();
		BeginMode2D(mainCamera);
		ClearBackground(bgColor);

		DrawUnifiedGrid2D(gridSize, spacing, gridColor, gridThickness, true);								 // TODO: Toggle grid visibility
		DrawRectangleLines(mouseGridPos.x * spacing, mouseGridPos.y * spacing, spacing, spacing, LIGHTGRAY); // TODO: Refactor to hoover function

		// DRAW CELLS
		for (int i = 0; i < cellArrayLength; i++)
		{
			DrawCell((Vector2){cellArrayPtr[i].x, cellArrayPtr[i].y}, spacing);
		}
		// POSTPROCESS CANVAS

		// DRAW UI
		{
			Color color = isPause ? RED : GREEN;
			Vector2 screenPos = GetScreenToWorld2D((Vector2){screenWidth - 50, screenHeight - 50}, mainCamera);
			DrawCircle(screenPos.x, screenPos.y, 10.f, color);
		}

		EndMode2D();
		DrawFPS(10, 10);
		EndDrawing();
	}
	// Heap cleanup
	free(cellArrayPtr);

	CloseWindow();
	return 0;
}