#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#define SCREEN_WIDTH        900
#define SCREEN_HEIGHT       600
#define MAX_FPS             60

#define WINDOW_TITLE        "3D Camera"

#define CAMERA_SPEED        1

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
    DrawCube(Vector3Zero(), 90, 90, 0, BLUE);
    DrawCube(Vector3Zero(), 0, 90, 90, DARKBLUE);
    DrawCube(Vector3Zero(), 90, 0, 90, DARKGREEN);
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

void checkDirection(double *horizontalDir, double *verticalDir)
{
    if (*horizontalDir > 360)
    {
        *horizontalDir = 0;
    }

    if (*horizontalDir < 0)
    {
        *horizontalDir = 360;
    }

    if (*verticalDir > 180)
    {
        *verticalDir = 180;
    }

    if (*verticalDir < -180)
    {
        *verticalDir = -180;
    }
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

    double horizontalDir = 0.0f;
    double verticalDir = 0.0f;

    while(!WindowShouldClose())
    {

        frameDelta = GetFrameTime();

        BeginDrawing();
            ClearBackground(DARKGRAY);

            BeginMode3D(mainCamera);
                drawAxis();
                drawWalls();
                DrawCube(Vector3Zero(), 1.0, 1.0, 1.0, YELLOW);
                checkDirection(&horizontalDir, &verticalDir);

                //if (IsKeyDown(KEY_W)) mainCamera.position.x += CAMERA_SPEED * frameDelta;
                //if (IsKeyDown(KEY_S)) mainCamera.position.x -= CAMERA_SPEED * frameDelta;
                //if (IsKeyDown(KEY_A)) mainCamera.position.y += CAMERA_SPEED * frameDelta;
                //if (IsKeyDown(KEY_D)) mainCamera.position.y -= CAMERA_SPEED * frameDelta;
                if (IsKeyPressed(KEY_R)) resetCameraPosition(&mainCamera);


                if (IsKeyDown(KEY_W)) verticalDir += CAMERA_SPEED * frameDelta * 30;
                if (IsKeyDown(KEY_S)) verticalDir -= CAMERA_SPEED * frameDelta * 30;
                if (IsKeyDown(KEY_D)) horizontalDir += CAMERA_SPEED * frameDelta * 30;
                if (IsKeyDown(KEY_A)) horizontalDir -= CAMERA_SPEED * frameDelta * 30;

                mainCamera.target.x = CAMERA_SPEED * sin((horizontalDir) * DEG2RAD) * cos((verticalDir) * DEG2RAD);
                mainCamera.target.y = CAMERA_SPEED * sin((horizontalDir) * DEG2RAD) * sin((verticalDir) * DEG2RAD);
                mainCamera.target.z = CAMERA_SPEED * cos((horizontalDir) * DEG2RAD);
                printf("Horizontal: %f\n", horizontalDir);
                printf("Vertical: %f\n", verticalDir);

            EndMode3D();

            drawCoords(&mainCamera);
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}