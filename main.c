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
	int windowWidth = 800;
	int windowHeight = 600;

	Color bgColor = {21, 30, 39, 255};

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(windowWidth, windowHeight, "C Game of Life");
	SetWindowMinSize(windowWidth, windowHeight);
	SetTargetFPS(60);

	Camera2D mainCamera = {0};
	mainCamera.target = (Vector2){-windowWidth / 2, -windowHeight / 2}; // camera pivot, left top
	mainCamera.zoom = 1.f;

	// Runtime config
	float spacing = 10;
	int gridSize = 100;
	Color gridColor = {100, 100, 100, 200};
	float gridThickness = .2f;

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

		if (IsKeyPressed(KEY_F1))
			ToggleFullscreen(); // TODO: resize window with fullscreen and get back
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			mainCamera.offset = Vector2Add(mainCamera.offset, GetMouseDelta()); // TODO: limit to grid size
		if (IsKeyPressed(KEY_SPACE))
			isPause = !isPause;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // can add or remove at least one
			cellArrayPtr = UpdateCellArray(cellArrayPtr, &cellArrayLength, mouseGridPos);

		// Time management
		logicCooldown += GetFrameTime();

		// MAIN LOGIC
		if (!isPause && logicCooldown > 0.1)
		{
			logicCooldown = 0;

			int survivedCount = HandleExistingCells(cellArrayPtr, cellArrayLength);
			Cell *spawnedArrayPtr = CellArray(survivedCount);
			int spawnedCount = SpawnNewCells(spawnedArrayPtr, cellArrayPtr, survivedCount);

			Cell *drawArrayPtr = ConcatenateCellArrays(cellArrayPtr, survivedCount, spawnedArrayPtr, spawnedCount);
			free(cellArrayPtr);
			free(spawnedArrayPtr);
			cellArrayPtr = drawArrayPtr;
			cellArrayLength = survivedCount + spawnedCount;
		}

		// DRAW CANVAS
		BeginDrawing();
		BeginMode2D(mainCamera);
		ClearBackground(bgColor);

		DrawUnifiedGrid2D(gridSize, spacing, gridColor, gridThickness, true);								 // TODO: Toggle grid visibility
		DrawRectangleLines(mouseGridPos.x * spacing, mouseGridPos.y * spacing, spacing, spacing, LIGHTGRAY); // TODO: Refactor to hoover function

		// visualize current cells state
		for (int i = 0; i < cellArrayLength; i++)
		{
			Cell current = cellArrayPtr[i];
			if (!current.isDead)
				DrawCell((Vector2){current.x, current.y}, spacing);
		}

		// POSTPROCESS CANVAS

		// DRAW UI
		{
			Color color = isPause ? RED : GREEN;
			Vector2 screenPos = GetScreenToWorld2D((Vector2){windowWidth - 50, windowHeight - 50}, mainCamera);
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