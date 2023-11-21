// Copyright (C) Arkadiusz Choruży

#include <stdbool.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "./src/app/window.h"
#include "./src/app/canvas.h"
#include "./src/logic/automata.h"
#include "./src/logic/cell.h"
#include "./src/logic/grid.h"
#include "./src/logic/grid_utils.h"
#include "./src/input/mouse.h"

int main()
{
	InitializeWindow();
	InitializeGrid();
	Grid grid = GetGrid();

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
		DrawCanvas(cellArrayPtr, cellArrayLength, isPause);
	}
	// Heap cleanup
	free(cellArrayPtr);

	CloseWindow();
	return 0;
}