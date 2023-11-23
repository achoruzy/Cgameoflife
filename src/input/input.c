// Copyright (C) Arkadiusz Choruży

#include "input.h"

static InputFlags inputFlags;

void InitializeUI()
{
    inputFlags.isPause = false;
}

InputFlags GetInputFlags() { return inputFlags; }