#include "raylib.h"
#include "Button.h"
int main(void)
{
    InitWindow(1600, 900, "Data Visualization");
    SetTargetFPS(60);
    Button test(800, 450, 300, 200, "Binary Search Tree");
    test.SetActiveColor(GREEN);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        test.render();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}