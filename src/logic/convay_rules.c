// Copyright (C) Arkadiusz Choruży


#include "convay_rules.h"

bool TryObeyRules(Cell* cell, int num_neighbors)
{
    // renew
    if (cell->isDead == true && num_neighbors == 3) 
    {
        cell->isDead = false;
        return true;
    }

    // kill definitely
    if (cell->isDead == true) return false;

    switch (num_neighbors)
    {
    case 2:
    case 3:
    cell->isDead = false;
        break;
    default: // kill temporary
        cell->isDead = true;
        break;
    }
    return true;
}