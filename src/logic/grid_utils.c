// Copyright (C) Arkadiusz Choruży

#include "grid_utils.h"

Vector2 WorldToGrid(Vector2 worldPos, float gridSpacing)
{
    float x = round(worldPos.x / gridSpacing);
    float y = round(worldPos.y / gridSpacing);
    return (Vector2){x, y};
}