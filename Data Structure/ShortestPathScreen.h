#ifndef SHORTESTPATHSCREEN_H
#define SHORTESTPATHSCREEN_H


#include "ShPController.h"
#include "ShortestPath.h"
#include "Button.h"
#include "ShPTextBox.h"

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

    // New members for input and edit modes
    bool inputMode;
    bool editMode;  // New flag
    ShPTextBox inputTextBox;
    Button submitButton;
};

#endif