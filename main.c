// Copyright (C) Arkadiusz Choruży

#include <stdbool.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "./src/app/window.h"
#include "./src/logic/automata.h"
#include "./src/logic/cell.h"
#include "./src/logic/grid.h"
#include "./src/logic/grid_utils.h"
#include "./src/draw/draw_grid.h"
#include "./src/draw/draw_cell.h"
#include "./src/input/input_handlers.h"
#include "./src/input/mouse.h"

int main()
{
	InitializeWindow();
	InitializeGrid();
	Grid grid = GetGrid();

	// float screenMargin = 25.f;
	float gridHalfWidth = grid.size * grid.spacing / 2;

	// Logic
	int cellArrayLength = 0;
	Cell *cellArrayPtr = CellArray(cellArrayLength);

	// UI flags
	bool isPause = true;

	// Time
	double logicCooldown = 0;

	while (!WindowShouldClose())
	{
		UpdateMouseInfo(GetWindow().camera, grid.spacing);

		int monitor = GetCurrentMonitor();
		if (IsKeyPressed(KEY_F1))
		{
			if (IsWindowFullscreen())
				SetWindowSize(GetWindow().width, GetWindow().height);
			else
				SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
			ToggleFullscreen();
		}
		if (IsKeyPressed(KEY_F2))
		{
			grid.isActive = !grid.isActive;
		}
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			UpdateCameraOffset(gridHalfWidth, gridHalfWidth);
		}
		if (IsKeyPressed(KEY_SPACE))
			isPause = !isPause;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // can add or remove at least one at a time
			UpdateCellArray(&cellArrayPtr, &cellArrayLength, GetMouseInfo().GridPos);

		// Time management
		logicCooldown += GetFrameTime();

		// MAIN LOGIC
		if (!isPause && logicCooldown > 0.2)
		{
			logicCooldown = 0;
			RunAutomata(&cellArrayPtr, &cellArrayLength);
		}

		// DRAW CANVAS
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
	// Heap cleanup
	free(cellArrayPtr);

	CloseWindow();
	return 0;
}