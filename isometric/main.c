#include <stdio.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>
#include <rcamera.h>
#include <rlgl.h>

#define SCREEN_WIDTH        1600
#define SCREEN_HEIGHT       900
#define MAX_FPS             60

#define WINDOW_TITLE        "Isometric"

typedef struct Player
{
    Vector3 pos;
    float direction;

} Player;

void checkPlayerDirection (Player *player)
{
    if (player->direction >= 360)
    {
        player->direction = 0;
    }

    if (player->direction < 0)
    {
        player->direction = 360;
    }
}


void drawAxis()
{
    DrawLine3D(Vector3Zero(), (Vector3){90, 0, 0}, BLUE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 90, 0}, RED);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, 90}, GREEN);

    DrawLine3D(Vector3Zero(), (Vector3){-90, 0, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, -90, 0}, WHITE);
    DrawLine3D(Vector3Zero(), (Vector3){0, 0, -90}, WHITE);
}

void handleInput(Player *player)
{
    checkPlayerDirection(player);

    if (IsKeyDown(KEY_A))
    {
        player->direction -= 1;
        printf("dir: %f\n", player->direction);
    }
    if (IsKeyDown(KEY_D))
    {
        player->direction += 1;
        printf("dir: %f\n", player->direction);
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

    Player p1 = {
        .pos = {.x = 0, .y = 0, .z = 2},
        .direction = 0
    };

    while(!WindowShouldClose())
    {
        BeginDrawing();
        BeginMode3D(mainCamera);

            ClearBackground(DARKGRAY);
            DrawPlane((Vector3){0, 0, 0}, (Vector2){90, 90}, BROWN);
            drawAxis();
            DrawGrid(90, 10);

            rlPushMatrix();
            rlTranslatef(5, 5, 5);
            rlRotatef(p1.direction, 0, 1, 0);
            DrawCube(p1.pos, 2, 2, 2, BLUE);
            rlPopMatrix();

            handleInput(&p1);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}