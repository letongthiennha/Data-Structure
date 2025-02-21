#include "raylib.h"
#include "Button.h"
#include "SLL.h"
int main(void)
{
    InitWindow(1600, 900, "Data Visualization");
    SetTargetFPS(1);
    LinkedList test;
    test.push_back(4);
    test.push_back(5);
    test.push_back(6);
    test.push_back(7);
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