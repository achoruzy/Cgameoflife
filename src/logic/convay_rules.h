// Copyright (C) Arkadiusz Choruży

#ifndef CONVAY_RULES_H_
#define CONVAY_RULES_H_

#include "cell.h"

#include <stdbool.h>

// When cell is empty but has 3 living cells around, then is to revive
bool isToRevive(int num_neighbors);

// When cell has 2 or 3 neighbors only it may live
bool isToLive(int num_neighbors);

#endif