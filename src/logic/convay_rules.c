// Copyright (C) Arkadiusz Choruży

#include "convay_rules.h"

bool isToRevive(const int num_neighbors) { return num_neighbors == 3; }

bool isToLive(const int num_neighbors)
{
    if (num_neighbors == 2 || num_neighbors == 3)
        return true;
    return false;
}
