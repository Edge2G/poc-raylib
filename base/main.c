#include <stdio.h>
#include <time.h>

#include <raylib.h>

#define SCREEN_WIDTH        900
#define SCREEN_HEIGHT       600
#define MAX_FPS             60

#define WINDOW_TITLE        "Base"

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetRandomSeed((unsigned)time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(MAX_FPS);

    double frameDelta;

    ClearBackground(DARKGRAY);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();

    printf("Raylib end...\n");
    return 0;
}