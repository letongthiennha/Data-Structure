#include "raylib.h"
#include "ShortestPathScreen.h"

int main() {
    InitWindow(1080, 960, "Shortest Path Visualization");
    SetTargetFPS(60);

    ShortestPathScreen sps;
    while (!WindowShouldClose()) {
        sps.update();
        sps.render();
    }

    CloseWindow();
    return 0;
}