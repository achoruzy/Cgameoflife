// Copyright (C) Arkadiusz Choruży

#include "convay_rules.h"

bool isToRevive(int num_neighbors) { return num_neighbors == 3; }

bool isToLive(int num_neighbors)
{
    if (num_neighbors == 2 || num_neighbors == 3)
        return true;
    return false;
}
