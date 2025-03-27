#include "raylib.h"
#include "ShortestPathNode.h"

int main() {
    // Initialize the window
    InitWindow(800, 600, "Shortest Path Node Test");
    SetTargetFPS(60);

    // Create a sample node
    ShPNode testNode({ 400, 300 }, 1);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the test node
        testNode.draw();

        EndDrawing();
    }

    CloseWindow(); // Close the window after exiting
    return 0;
}
