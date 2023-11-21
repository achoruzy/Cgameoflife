// Copyright (C) Arkadiusz Choruży

#include "window.h"

static AppWindow appWindow;

void InitializeWindow()
{
    appWindow.width = 800;
    appWindow.height = 600;
    appWindow.minWidth = 800;
    appWindow.minHeight = 600;
    appWindow.title = "C Game of Life";
    appWindow.bgColor = (Color){21, 30, 39, 255};

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(appWindow.width, appWindow.height, appWindow.title);
    SetWindowMinSize(appWindow.minWidth, appWindow.minHeight);
    SetTargetFPS(60);

    Camera2D mainCamera = {0};
    mainCamera.target = (Vector2){-appWindow.width / 2, -appWindow.height / 2}; // camera pivot, left top
    mainCamera.zoom = 1.f;

    appWindow.camera = mainCamera;
}

AppWindow GetWindow() { return appWindow; }

void UpdateCameraOffset(int gridHalfWidth, int gridHalfHeight)
{
    float screenMargin = 25.f;

    appWindow.camera.offset = Vector2Clamp(
        Vector2Add(appWindow.camera.offset, GetMouseDelta()),
        (Vector2){-gridHalfWidth + (GetWindow().width / 2) - screenMargin,
                  -gridHalfHeight + (GetWindow().height / 2) - screenMargin},
        (Vector2){gridHalfWidth - (GetWindow().width / 2) + screenMargin,
                  gridHalfHeight - (GetWindow().height / 2) + screenMargin});
}