#include "ShPController.h"
#include "ShortestPath.h"
#include <string>

std::string ShPController::formatSpeed(float speed) {
    std::ostringstream oss;
    oss << "Speed: " << std::fixed << std::setprecision(1) << speed << "x";
    return oss.str();
}

ShPController::ShPController()
    : startVertexTextBox({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y + stateControlButtonSize.y }, { stateControlButtonSize.x * 2, stateControlButtonSize.y }, WHITE, BLACK, 2) {

    OperationBoard.x = operationBoardPosition.x;
    OperationBoard.y = operationBoardPosition.y;
    OperationBoard.width = operationBoardSize.x;
    OperationBoard.height = operationBoardSize.y;

    Random.setText("Random", 20);
    Random.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Random.setPosition(stateControlPosition);
    Random.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Input.setText("Input", 20);
    Input.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Input.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 2, stateControlPosition.y });
    Input.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    LoadFile.setText("Load File", 20);
    LoadFile.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    LoadFile.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 4, stateControlPosition.y });
    LoadFile.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Edit.setText("Edit", 20);
    Edit.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Edit.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 6, stateControlPosition.y });
    Edit.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Dijkstra.setText("Dijkstra", 20);
    Dijkstra.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Dijkstra.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y });
    Dijkstra.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 20);
    SpeedButton.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    SpeedButton.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y - stateControlButtonSize.y});
    SpeedButton.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option05x.setText("0.5x", 20);
    Option05x.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Option05x.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y - stateControlButtonSize.y*2 });
    Option05x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option1x.setText("1x", 20);
    Option1x.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Option1x.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y - stateControlButtonSize.y * 3 });
    Option1x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option2x.setText("2x", 20);
    Option2x.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Option2x.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y - stateControlButtonSize.y * 4 });
    Option2x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option4x.setText("4x", 20);
    Option4x.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Option4x.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 8, stateControlPosition.y - stateControlButtonSize.y * 5 });
    Option4x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    startVertexTextBox.setText("0");
}

ShPController::~ShPController() {}

void ShPController::update() {
    Random.update();
    Input.update();
    Edit.update();
    Dijkstra.update();
    LoadFile.update();
    SpeedButton.update();
    startVertexTextBox.update();

    if (SpeedButton.isClicked()) {
        isSpeedDropdownOpen = !isSpeedDropdownOpen;
    }

    if (isSpeedDropdownOpen) {
        Option05x.update();
        if (Option05x.isClicked()) {
            currentSpeed = 0.5f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 20);
        }
        Option1x.update();
        if (Option1x.isClicked()) {
            currentSpeed = 1.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 20);
        }
        Option2x.update();
        if (Option2x.isClicked()) {
            currentSpeed = 2.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 20);
        }
        Option4x.update();
        if (Option4x.isClicked()) {
            currentSpeed = 4.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 20);
        }
    }
}

void ShPController::render() {
    Random.drawRectangle();
    Input.drawRectangle();
    Dijkstra.drawRectangle();
    LoadFile.drawRectangle();
    Edit.drawRectangle();
    SpeedButton.drawRectangle();
    startVertexTextBox.render();

    Random.drawText(BLACK);
    Input.drawText(BLACK);
    Dijkstra.drawText(BLACK);
    LoadFile.drawText(BLACK);
    Edit.drawText(BLACK);
    SpeedButton.drawText(BLACK);

    if (isSpeedDropdownOpen) {
        Option05x.drawRectangle();
        Option05x.drawText(BLACK);
        Option1x.drawRectangle();
        Option1x.drawText(BLACK);
        Option2x.drawRectangle();
        Option2x.drawText(BLACK);
        Option4x.drawRectangle();
        Option4x.drawText(BLACK);
    }
}

bool ShPController::isRandomClicked() const {
    return Random.isClicked();
}

bool ShPController::isInputClicked() const {
    return Input.isClicked();
}

bool ShPController::isLoadFileClicked() const {
    return LoadFile.isClicked();
}

bool ShPController::isEditClicked() const {
    return Edit.isClicked();
}

bool ShPController::isDijkstraClicked() const {
    return Dijkstra.isClicked();
}

int ShPController::getStartVertex() {
    std::string startVertexStr = startVertexTextBox.getText();
    return std::stoi(startVertexStr);
}