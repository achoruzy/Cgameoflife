#include <raylib.h>
#include <rlgl.h>


// Draw a unified 2D grid. 
static void DrawUnifiedGrid2D(int size, float spacing, Color color, float thickness)
{
    float gridSize = size * spacing;
    float halfGridSize = gridSize / 2;

    rlBegin(RL_LINES);
    rlSetLineWidth(thickness);
    rlColor4f(color.r, color.g, color.b, color.a);

    float ixspacing;
    for (int i = 0; i <= size; i++) 
    {
        ixspacing = i * spacing;
        rlVertex2f(0, ixspacing);
        rlVertex2f(gridSize, ixspacing);

        rlVertex2f(ixspacing, 0);
        rlVertex2f(ixspacing, gridSize);
    }
    rlEnd();
}