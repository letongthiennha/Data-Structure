#include "raylib.h"
#include "Font.h"
#include "ShortestPathScreen.h"

int main() {
    InitWindow(1280, 960, "Shortest Path Visualization");
    SetTargetFPS(60);

    ShortestPathScreen screen;
    
    while (!WindowShouldClose()) {
        screen.update();
        BeginDrawing();
        screen.render();
        EndDrawing();
    }
    UnloadFont(arial);
    CloseWindow();
    return 0;
}