// Copyright (C) Arkadiusz Choruży

#include "draw_cell.h"

void DrawCell(int x, int y, float spacing, Color color)
{
	float dilatation = 0.05f;
	float cellSize = spacing - 2 * dilatation;

	Rectangle cell = {
		x * spacing + dilatation,
		y * spacing + dilatation,
		cellSize,
		cellSize};

	DrawRectangleRounded(cell, 0.3, 2, color);
}