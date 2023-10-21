#include <raylib.h>
#include <rlgl.h>

void DrawCell(float spacing)
{
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
}