// Copyright (C) Arkadiusz Choruży


#include "convay_rules.h"

bool TryObeyRules(Cell* cell, int num_neighbors)
{
    if (cell->isDead == true && num_neighbors == 3) 
    {
        cell->isDead = false;
    }

    if (cell->isDead == false) return false;

    switch (num_neighbors)
    {
    case 2:
    case 3:
        break;
    default:
        cell->isDead == true;
        break;
    }
}