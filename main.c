#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/draw/grid.c"
#include "./src/draw/cell.c"
#include "./src/ui/debug.c"

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
		if (IsKeyPressed(299)) ToggleFullscreen(); // TODO: resize window with fullscreen and get back

		if (IsMouseButtonDown(1)) mainCamera.offset = Vector2Add(mainCamera.offset, GetMouseDelta());

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
		DrawCell(spacing);

		DrawCircle(100, 50, 50, YELLOW);
		DrawCircleLines(0, 0, 30, RED);
		EndMode2D();
		// postprocess
		// draw UI
		DrawFPS(10, 10);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}