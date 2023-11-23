// Copyright (C) Arkadiusz Choruży

#ifndef INPUT_H_
#define INPUT_H_

#include <stdbool.h>

typedef struct
{
    bool isPause;
} InputFlags;

void InitializeUI()
{
    inputFlags.isPause = false;
}

InputFlags GetInputFlags()

#endif