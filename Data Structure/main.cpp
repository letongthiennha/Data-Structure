#include "raylib.h"
#include "shortestpath.h"

int main() {
    InitWindow(800, 600, "Shortest Path Visualization");
    SetTargetFPS(60);

    ShortestPath sp;

    // Create a random graph
    sp.createRandomGraph(8, 0.2f, 11); // 10 nodes, 20% edge probability, weights 1-10

    // Start Dijkstra's algorithm from node 0
    int startId = 0;
    int endId = 9;
    sp.startDijkstra(startId);

    // Variables for delay control
    float timeSinceLastStep = 0;
    float delay = 0.5f; // 0.5 seconds delay between steps
    bool animating = true;

    while (!WindowShouldClose()) {
        if (animating) {
            timeSinceLastStep += GetFrameTime();
            if (timeSinceLastStep >= delay) {
                timeSinceLastStep = 0;
                if (!sp.stepDijkstra()) {
                    animating = false;
                    sp.highlightPath(endId); // Highlight the final path after animation
                }
            }
        }

        sp.renderGraph(); // Render the graph each frame
    }

    CloseWindow();
    return 0;
}