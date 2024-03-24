#include <stdio.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>

#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900
#define MAX_FPS             60

#define WINDOW_TITLE        "Isometric"

void drawAxis()
{
    DrawLine3D(Vector3Zero(), (Vector3){90, 0, 0}, BLUE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 90, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, 90}, GREEN);

    DrawLine3D(Vector3Zero(), (Vector3){-90, 0, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, -90, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, -90}, WHITE);
}

void handleInput(Camera3D *camera)
{
    if (IsKeyDown(KEY_W))
    {
        camera->position.z += 1;
    }
    if (IsKeyDown(KEY_S))
    {
        camera->position.z -= 1;
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        camera->target.x += 1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        camera->target.x -= 1;
    }
}

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetRandomSeed((unsigned)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(MAX_FPS);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    double frameDelta;

    Camera3D mainCamera = {
        .position = {0, 10, 10},
        .target = Vector3Zero(),
        .up = {0, 1, 0},
        .fovy = 90,
        .projection = CAMERA_PERSPECTIVE
    };

    while(!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode3D(mainCamera);

            ClearBackground(DARKGRAY);
            DrawPlane((Vector3){0, 0, 0}, (Vector2){90, 90}, BROWN);
            drawAxis();
            DrawGrid(90, 10);
            DrawCube((Vector3){0, 0, 2}, 2, 2, 2, BLUE);

            handleInput(&mainCamera);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}