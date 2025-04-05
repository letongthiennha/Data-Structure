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

    bool inputMode;
    bool editMode;  
    ShPTextBox inputTextBox;
    Button submitButton;
};

#endif