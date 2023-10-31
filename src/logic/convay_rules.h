// Copyright (C) Arkadiusz Choruży

#ifndef CONVAY_RULES_H_
#define CONVAY_RULES_H_

#include "cell.h"

#include <stdbool.h>

bool TryObeyRules(Cell *cell, int num_neighbors);

bool isToRevive(int num_neighbors);
bool isToLive(int num_neighbors);

#endif