#pragma once
#include "Button.h"
#include "Setting.h"
#include "TextBox.h"
#include <sstream>
#include <iomanip>

class ShPController {
public:
    ShPController();
    ~ShPController();
    bool isRandomClicked() const;
    bool isPauseClicked() const;
    bool isNextClicked() const;
    bool isPrevClicked() const;
    void setPauseText(const std::string& text);
    bool isInputClicked() const;
    bool isDijkstraClicked() const;
    bool isLoadFileClicked() const;
    bool isEditClicked() const;
    int getStartVertex();
    float getSpeed() const { return currentSpeed; }
    virtual void update();
    virtual void render();
    TextBox startVertexTextBox;
    std::string formatSpeed(float speed);

protected:
    Button Random;
    Button Pause;
    Button Next;
    Button Prev;
    Button Input;
    Button Dijkstra;
    Button LoadFile;
    Button Edit;
    Button SpeedButton;
    bool isSpeedDropdownOpen = false;
    Button Option05x;
    Button Option1x;
    Button Option2x;
    Button Option4x;
    float currentSpeed = 1.0f;
    Rectangle OperationBoard;
};