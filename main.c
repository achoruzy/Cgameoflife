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

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
	InitWindow(windowWidth, windowHeight, "C Game of Life");
	SetWindowMinSize(windowWidth, windowHeight);
	SetTargetFPS(60);

	Camera2D mainCamera = {0};
	mainCamera.target =  (Vector2){ 0.0f, 0.0f };
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
			rlTranslatef(0, 25*50, 0);
			rlRotatef(90, 1, 0, 0);
			DrawCustomGrid(100, 50, (Vector3){0.2, 0.2, 0.7}, 2.f);
		rlPopMatrix();
			// grid lines (with turn off)
			// spawning cells
		DrawCircle(100, 100, 50, YELLOW);
		EndMode2D();
		// postprocess
		// draw UI
		EndDrawing();
	}
	CloseWindow();
	return 0;
}