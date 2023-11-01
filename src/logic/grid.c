// Copyright (C) Arkadiusz Choruży

#include "grid.h"

Vector2 WorldToGrid(Vector2 worldPos, float gridSpacing) // TODO: Refactor to other place
{
    float x = round(worldPos.x / gridSpacing);
    float y = round(worldPos.y / gridSpacing);
    return (Vector2){x, y};
}