#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>
#include <rcamera.h>
#include <raymath.h>

#define SCREEN_WIDTH        900
#define SCREEN_HEIGHT       600
#define MAX_FPS             60

#define WINDOW_TITLE        "3D Camera"

#define CAMERA_SPEED        0.8f

void drawAxis()
{
    DrawLine3D(Vector3Zero(), (Vector3){90, 0, 0}, BLUE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 90, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, 90}, GREEN);

    DrawLine3D(Vector3Zero(), (Vector3){-90, 0, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, -90, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, -90}, WHITE);
}

void drawWalls()
{
    DrawPlane(Vector3Zero(), (Vector2){20.0f, 20.0f}, GRAY);
}

void drawCoords(Camera *camera)
{
    DrawText(TextFormat("%.2f", camera->position.x), 10, 10, 20, WHITE);
    DrawText(TextFormat("%.2f", camera->position.y), 110, 10, 20, WHITE);
    DrawText(TextFormat("%.2f", camera->position.z), 210, 10, 20, WHITE);
}

void resetCameraPosition(Camera *camera)
{
    camera->position.x = 0;
    camera->position.y = 0;
    camera->position.z = 4;
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

    DisableCursor();

    double horizontalDir = 0.0f;
    double verticalDir = 0.0f;

    while(!WindowShouldClose())
    {

        frameDelta = GetFrameTime();
        //UpdateCamera(&mainCamera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode3D(mainCamera);
                drawAxis();
                drawWalls();
                DrawCube(Vector3Zero(), 1.0, 1.0, 1.0, YELLOW);

                if (IsKeyPressed(KEY_R)) resetCameraPosition(&mainCamera);
                if (IsKeyDown(KEY_W)) CameraMoveForward(&mainCamera, CAMERA_SPEED, 1);
                if (IsKeyDown(KEY_A)) CameraMoveRight(&mainCamera, -CAMERA_SPEED, 1);
                if (IsKeyDown(KEY_S)) CameraMoveForward(&mainCamera, -CAMERA_SPEED, 1);
                if (IsKeyDown(KEY_D)) CameraMoveRight(&mainCamera, CAMERA_SPEED, 1);
                if (IsKeyDown(KEY_SPACE)) CameraMoveUp(&mainCamera, CAMERA_SPEED);
            EndMode3D();

            drawCoords(&mainCamera);
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}