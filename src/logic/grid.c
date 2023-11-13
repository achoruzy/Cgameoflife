// Copyright (C) Arkadiusz Choruży

#include "grid.h"

Vector2 WorldToGrid(const Vector2 worldPos, const float gridSpacing)
{
    const float x = round(worldPos.x / gridSpacing);
    const float y = round(worldPos.y / gridSpacing);
    return (Vector2){x, y};
}