// Copyright (C) Arkadiusz Choruży

#ifndef INPUT_H_
#define INPUT_H_

#include <stdbool.h>
#include <raylib.h>

#include "../input/mouse.h"
#include "../app/window.h"
#include "../logic/grid.h"

typedef struct
{
    bool isPause;
} InputFlags;

void InitializeInput();
InputFlags GetInputFlags();
void ProcessInput();

static void ProcessToggleFullscreen();
static void ProcessToggleGridActive();
static void ProcessCameraMove();
static void ProcessAutomataPause();

#endif