#pragma once

#include "ShortestPath.h"

class ShortestPathScreen {
public:
    void render();
    void update();
    ShortestPath sp;
private:
    float timeSinceLastStep;
    float delay = 0.5f;
    bool animating = true;
};
