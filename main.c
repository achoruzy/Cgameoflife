#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/draw/grid.c"

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

	while (!WindowShouldClose())
    {
		if (IsKeyPressed(299)) ToggleFullscreen(); // TODO: resize window with fullscreen and get back
		// get input
		// use input (UI logic and gameplay)

		BeginDrawing();
		BeginMode2D(mainCamera);
		ClearBackground(bgColor);
		// draw game
			// grid matrix
		int spacing = 10;
		DrawUnifiedGrid2D(100, spacing, (Color){100, 100, 100, 200}, .2f, true);
			// grid lines (with turn off)
			// spawning cells
		int column = 0;
		int row = 0;
		float dilatation = 0.05f;
		Rectangle cell = {
			0+dilatation+column*spacing,
			0+dilatation+column*spacing,
			spacing-2*dilatation,
			spacing-2*dilatation
			};
		
		DrawRectangleRounded(cell, 0.3, 2, WHITE);


		DrawCircle(100, 50, 50, YELLOW);
		DrawCircleLines(0, 0, 30, RED);
		EndMode2D();
		// postprocess
		// draw UI
		EndDrawing();
	}
	CloseWindow();
	return 0;
}