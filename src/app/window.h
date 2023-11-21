// Copyright (C) Arkadiusz Choruży

#ifndef WINDOW_H_
#define WINDOW_H_

#include <raylib.h>
#include <stdbool.h>
#include <raymath.h>

typedef struct
{
    int width;
    int height;
    int minWidth;
    int minHeight;
    char *title;
    Color bgColor;
    Camera2D camera;
} AppWindow;

void InitializeWindow();
AppWindow GetWindow();
void UpdateCameraOffset(int gridHalfWidth, int gridHalfHeight);

#endif