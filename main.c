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
#include "./src/input/input.h"

int main()
{
	InitializeWindow();
	InitializeInput();
	InitializeGrid();
	Grid grid = GetGrid();

	int cellArrayLength = 0;
	Cell *cellArrayPtr = CellArray(cellArrayLength);

	bool isPause = true;

	// Time
	double logicCooldown = 0;

	while (!WindowShouldClose())
	{
		logicCooldown += GetFrameTime();
		ProcessInput();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) // can add or remove at least one at a time
			UpdateCellArray(&cellArrayPtr, &cellArrayLength, GetMouseInfo().GridPos);

		// MAIN LOGIC
		if (!GetInputFlags().isPause && logicCooldown > 0.2)
		{
			logicCooldown = 0;
			RunAutomata(&cellArrayPtr, &cellArrayLength);
		}

		// DRAW CANVAS
		DrawCanvas(cellArrayPtr, cellArrayLength, GetInputFlags().isPause);
	}
	// Heap cleanup
	free(cellArrayPtr);

	CloseWindow();
	return 0;
}