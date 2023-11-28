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
#include "./src/input/input.h"
#include "./src/sound/sound.h"

int main()
{
	InitializeWindow();
	InitializeAudio();
	InitializeInput();
	InitializeGrid();
	InitializeMainCellArray();
	InitializeCanvas();

	double logicCooldown = 0;
	while (!WindowShouldClose())
	{
		logicCooldown += GetFrameTime();
		ProcessInput();
		// MAIN LOGIC
		if (!GetInputFlags().isPause && logicCooldown > 0.2)
		{
			logicCooldown = 0;
			RunAutomata();
		}
		// DRAW CANVAS
		DrawCanvas();
	}
	// Heap cleanup
	FreeMainCellArray();
	DeinitializeCanvas();
	DeinitializeAudio();
	CloseWindow();
	return 0;
}