// Copyright (C) Arkadiusz Choruży


#include "draw_cell.h"


void DrawCell(Vector2 gridPos, float spacing)
{
    int row = gridPos.x;
	int column = gridPos.y;
	float dilatation = 0.05f;
	float cellSize = spacing-2*dilatation;

	Rectangle cell = {
		row * spacing + dilatation,
		column * spacing + dilatation,
		cellSize,
		cellSize
		};
	
	DrawRectangleRounded(cell, 0.3, 2, WHITE);
}