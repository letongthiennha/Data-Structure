#include "ShortestPathScreen.h"
#include "raylib.h"

ShortestPathScreen::ShortestPathScreen() : animating(true), timeSinceLastStep(0), delay(0.5f) {
    ctrl = ShPController();
}

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
    sp.renderGraph();
    ctrl.render();
}

void ShortestPathScreen::update() {
    ctrl.update();

    if (ctrl.isRandomClicked()) {
        sp.clearGraph();
        sp.createRandomGraph();
    }
    if (ctrl.isDijkstraClicked()) {
        int startId = ctrl.getStartVertex();
        sp.startDijkstra(startId);
        timeSinceLastStep = 0;
        animating = true;
    }
}