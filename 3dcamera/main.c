#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH        900
#define SCREEN_HEIGHT       600
#define MAX_FPS             60

#define WINDOW_TITLE        "3D Camera"

void drawAxis()
{
    DrawLine3D(Vector3Zero(), (Vector3){90, 0, 0}, BLUE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 90, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, 90}, GREEN);
}

void drawCoords(Camera *camera)
{
    char nx[10], ny[10], nz[10];
    

    DrawText(nx, 100, 100, 20, WHITE);
}

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetRandomSeed((unsigned)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(MAX_FPS);

    double frameDelta;

    Camera3D mainCamera = {
        .position = {0, 0, 4},
        .target = Vector3Zero(),
        .up = {0, 1, 0},
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE
    };

    while(!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            drawCoords(&mainCamera);

            BeginMode3D(mainCamera);
                drawAxis();
                DrawCube(Vector3Zero(), 1.0, 1.0, 1.0, YELLOW);

                if (IsKeyDown(KEY_W)) mainCamera.position.x += 0.1;
                if (IsKeyDown(KEY_S)) mainCamera.position.x -= 0.1;
                if (IsKeyDown(KEY_A)) mainCamera.position.y += 0.1;
                if (IsKeyDown(KEY_D)) mainCamera.position.y -= 0.1;

            EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}