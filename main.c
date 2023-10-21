#include <stdio.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "./src/utils/drawUtils.c"

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
		rlPushMatrix();
			DrawUnifiedGrid2D(100, 10, (Color){80, 80, 150, 200}, 1.f);
		rlPopMatrix();
			// grid lines (with turn off)
			// spawning cells
		DrawCircle(100, 50, 50, YELLOW);
		EndMode2D();
		// postprocess
		// draw UI
		EndDrawing();
	}
	CloseWindow();
	return 0;
}