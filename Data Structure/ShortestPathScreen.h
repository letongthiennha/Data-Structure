#ifndef SHORTESTPATHSCREEN_H
#define SHORTESTPATHSCREEN_H


#include "ShPController.h"
#include "ShortestPath.h"
#include "Button.h"
#include "ShPTextBox.h"
#include <vector> 
#include <string>

class ShortestPathScreen {
public:
    ShortestPathScreen();
    void render();
    void update();
    bool goBack();

private:
    ShPController ctrl;
    ShortestPath sp;
    bool animating;
    float timeSinceLastStep;
    float delay;
	float baseDelay = 0.8f;
    ShPNode* draggingNode = nullptr;

    bool inputMode;
    bool editMode;  
    ShPTextBox inputTextBox;
    Button submitButton;
    std::vector<std::string> pseudoCodeLines;
    int currentStep;
    Button Home;
    bool isPaused = false;
};

#endif