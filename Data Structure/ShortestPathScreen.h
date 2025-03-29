#ifndef SHORTESTPATHSCREEN_H
#define SHORTESTPATHSCREEN_H

#include "ShPController.h"
#include "ShortestPath.h"

class ShortestPathScreen {
public:
    ShortestPathScreen();
    void render();
    void update();

private:
    ShPController ctrl;
    ShortestPath sp;
    bool animating;
    float timeSinceLastStep;
    float delay;
};
#endif