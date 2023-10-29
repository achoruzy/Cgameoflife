// Copyright (C) Arkadiusz Choruży

#include "convay_rules.h"

bool TryObeyRules(Cell *cell, int num_neighbors)
{
    // kill definitely
    if (cell->isDead == true)
        return false;

    bool isCellToLive = isToLive(num_neighbors);
    cell->isDead = isCellToLive;
    return true;
}

// When cell is empty but has 3 living cells around, then is to revive
bool isToRevive(int num_neighbors) { return num_neighbors == 3; }

// When cell has 2 or 3 neighbors only it may live
static bool isToLive(int num_neighbors)
{
    if (num_neighbors == 2 || num_neighbors == 3)
        return true;
    return false;
}
