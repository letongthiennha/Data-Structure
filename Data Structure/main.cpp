#include "raylib.h"
#include "ShortestPath.h"
#include "ShortestPathScreen.h"

int main() {
    InitWindow(1080, 960, "Shortest Path Visualization");
    SetTargetFPS(60);
    ShortestPathScreen sps;
    sps.update();
    while (!WindowShouldClose()){
		sps.render();
	}
    CloseWindow();
    return 0;
}