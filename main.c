#include <stdio.h>
#include <raylib.h>

int main()
{
	int windowWidth = 800;
	int windowHeight = 600;

	Color bgColor = { 21, 30, 39, 255 };


	InitWindow(windowWidth, windowHeight, "C Game of Life");
	SetTargetFPS(60);

	Camera2D mainCamera = {0};
	mainCamera.zoom = 1.f;

	while (!WindowShouldClose())
    {
		// get input
		// use input (UI logic and gameplay)

		BeginDrawing();
		ClearBackground(bgColor);
		// draw game
			// grid matrix
			// grid lines (with turn off)
			// spawning cells
		// postprocess
		// draw UI
		EndDrawing();
	}
	CloseWindow();
	return 0;
}