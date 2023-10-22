#include <stdio.h>
#include <math.h>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/draw/grid.c"
#include "./src/draw/cell.c"
#include "./src/ui/debug.c"


Vector2 WorldToGrid(Vector2 worldPos, float gridSpacing)
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

	while (!WindowShouldClose())
    {
		Vector2 mouseScreenPos = GetMousePosition();
		Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, mainCamera);

		if (IsKeyPressed(299)) ToggleFullscreen(); // TODO: resize window with fullscreen and get back
		if (IsMouseButtonDown(1)) mainCamera.offset = Vector2Add(mainCamera.offset, GetMouseDelta()); // TODO: limit to grid size

		Vector2 mouseGridPos = WorldToGrid(mouseWorldPos, spacing);

		// printf("x: %f, y: %f\n",mouseWorldPos.x,mouseWorldPos.y);
		printf("x: %f, y: %f\n", mouseGridPos.x * spacing, mouseGridPos.y * spacing);
			// get mouse pos
			// mouse pos to grid pos


		// get input
		// use input (UI logic and gameplay)

		BeginDrawing();
		BeginMode2D(mainCamera);
		ClearBackground(bgColor);
		// draw game
			// grid matrix
		DrawUnifiedGrid2D(gridSize, spacing, gridColor, gridThickness, true);
			// grid lines (with turn off)
			// spawning cells

		DrawRectangleLines(mouseGridPos.x * spacing, mouseGridPos.y * spacing, spacing, spacing, LIGHTGRAY);

		if (IsMouseButtonDown(0))
		{
			// draw cell
			DrawCell(mouseGridPos, spacing);
		}
		DrawCell(Vector2Zero(), spacing);

		// DrawCircle(100, 50, 50, YELLOW);
		// DrawCircleLines(0, 0, 30, RED);
		EndMode2D();
		// postprocess
		// draw UI
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}