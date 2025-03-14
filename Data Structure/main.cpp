#include "raylib.h"
#include "Button.h"
#include "SLL.h"
#include "movableObject.h"
int main(void){
    InitWindow(800, 600, "test");
    Rectangle a;
    a.width = 200;
    a.height = 200;
    a.x = 100.0f;
    a.y = 100.0f;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleRounded(a, 1.0f, 500, RED);
        EndDrawing();
    }
    return 0;
}