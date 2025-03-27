#include "ShortestPathScreen.h"
#include "raylib.h"




void ShortestPathScreen::render() {
    if (animating) {
        timeSinceLastStep += GetFrameTime();
        if (timeSinceLastStep >= delay) {
            timeSinceLastStep = 0;
            if (!sp.stepDijkstra()) {
                animating = false;
            }
        }
    }

    sp.renderGraph(); // Render the graph each frame
}

void ShortestPathScreen::update() {
    sp.createRandomGraph(0.25f);
    int startId = 0;
    sp.startDijkstra(startId);
    float timeSinceLastStep = 0;
    float delay = 0.5f;
    bool animating = true;
}
