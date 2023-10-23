#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/draw/grid.c"
#include "./src/draw/cell.c"
#include "./src/ui/debug.c"
#include "./src/logic/logic.c"


Vector2 WorldToGrid(Vector2 worldPos, float gridSpacing) // TODO: Refactor to other place
{
	float x = round(worldPos.x / gridSpacing);
	float y = round(worldPos.y / gridSpacing);
	return (Vector2){x, y};
}

int main()
{
	int windowWidth = 800;
	int windowHeight = 600;

	Color bgColor = { 21, 30, 39, 255 };

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
	InitWindow(windowWidth, windowHeight, "C Game of Life");
	SetWindowMinSize(windowWidth, windowHeight);
	SetTargetFPS(60);

	Camera2D mainCamera = {0};
	mainCamera.target =  (Vector2){ -windowWidth/2, -windowHeight/2 }; // camera pivot, left top
	mainCamera.zoom = 1.f;

	// Runtime config
	float spacing = 10;
	int gridSize = 100;
	Color gridColor = {100, 100, 100, 200};
	float gridThickness = .2f;

	// Logic
	int cellArrayLength = 0;
	Cell* cellArray = CellArray(cellArrayLength);
	// Cell cellArray[32];

	while (!WindowShouldClose())
    {
		Vector2 mouseScreenPos = GetMousePosition();
		Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, mainCamera);
		Vector2 mouseGridPos = WorldToGrid(mouseWorldPos, spacing);

		if (IsKeyPressed(299)) ToggleFullscreen(); // TODO: resize window with fullscreen and get back
		if (IsMouseButtonDown(1)) mainCamera.offset = Vector2Add(mainCamera.offset, GetMouseDelta()); // TODO: limit to grid size

		if (IsMouseButtonDown(0)) // can add or remove at least one 
		{
			// check for already exist and remove cell
			bool removed = false;
			for (int i = 0; i < cellArrayLength; i++)
			{
				Cell* current = cellArray + i;
				if (current->x == (int)mouseGridPos.x && current->y == (int)mouseGridPos.y)
				{
					// remove
					cellArrayLength--;
					removed = true;
				}
			}

			// append
			if (!removed)
			{
				cellArrayLength++;
				Cell* newArray = CellArray(cellArrayLength);

				for (int i = 0; i < cellArrayLength - 1; i++)
				{
					newArray[i] = cellArray[i];
				}
				newArray[cellArrayLength - 1] = (Cell){mouseGridPos.x, mouseGridPos.y, false, 0};
				
				free(cellArray);
				cellArray = newArray; // newArray not to free here as cellArray gots the address
			}
		}

		// printf("x: %f, y: %f\n",mouseWorldPos.x,mouseWorldPos.y);
		// printf("x: %f, y: %f\n", mouseGridPos.x * spacing, mouseGridPos.y * spacing);
		
		// draw game
		BeginDrawing();
		BeginMode2D(mainCamera);
		ClearBackground(bgColor);

		DrawUnifiedGrid2D(gridSize, spacing, gridColor, gridThickness, true); // TODO: Toggle grid visibility
		DrawRectangleLines(mouseGridPos.x * spacing, mouseGridPos.y * spacing, spacing, spacing, LIGHTGRAY); // TODO: Refactor to hoover function

		// game of life logic

		// visualize current cells state
		for (int i = 0; i < cellArrayLength; i++)
		{
			Cell current = cellArray[i];
			if (!current.isDead) DrawCell((Vector2){current.x, current.y}, spacing);
			// printf("%i, %i, %i, %i\n", current.x, current.y, current.isDead, current.neighbours);
		}

		EndMode2D();
		// postprocess
		// draw UI
		DrawFPS(10, 10);
		EndDrawing();
	}
	// Heap cleanup
	free(cellArray);

	CloseWindow();
	return 0;
}