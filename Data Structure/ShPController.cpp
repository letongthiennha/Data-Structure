#include "ShPController.h"
#include "ShortestPath.h"
#include <string>


std::string ShPController::formatSpeed(float speed) {
    std::ostringstream oss;
    oss << "Speed: " << std::fixed << std::setprecision(1) << speed << "x";
    return oss.str();
}

ShPController::ShPController()
    : startVertexTextBox({ 0, 0 }, { 75, 60 }, WHITE, BLACK, 2) {

    // Define specific values for operationBoardPosition and stateControlButtonSize
    Vector2 operationBoardPosition = { 850, 650 };
    Vector2 operationBoardSize = { 1600, 200 };
    Vector2 stateControlButtonSize = { 150, 60 };

    OperationBoard.x = operationBoardPosition.x;
    OperationBoard.y = operationBoardPosition.y;
    OperationBoard.width = operationBoardSize.x;
    OperationBoard.height = operationBoardSize.y;

    // Calculate row spacing (button height + 10 pixels)
    float rowSpacing = stateControlButtonSize.y + 10;

    // Bottom row: Start Vertex and Speed
    float bottomRowY = operationBoardPosition.y + 160; // y = 860 (700 + 160)

    startVertexTextBox.setPosition({ operationBoardPosition.x + 10, bottomRowY });

    SpeedButton.setText("Speed", 20);
    SpeedButton.setSize(stateControlButtonSize);
    SpeedButton.setPosition({ operationBoardPosition.x + 90, bottomRowY });
    SpeedButton.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    float speedOptionsX = SpeedButton.getPosition().x + stateControlButtonSize.x + 10;
    float speedOptionsY = bottomRowY;

    Option05x.setText("0.5x", 20);
    Option05x.setSize({ stateControlButtonSize.x * 0.5f, stateControlButtonSize.y }); // {50, 40}
    Option05x.setPosition({ speedOptionsX, speedOptionsY });
    Option05x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option1x.setText("1x", 20);
    Option1x.setSize({ stateControlButtonSize.x * 0.5f, stateControlButtonSize.y });
    Option1x.setPosition({ speedOptionsX + stateControlButtonSize.x * 0.5f + 5, speedOptionsY }); // x = 180
    Option1x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option2x.setText("2x", 20);
    Option2x.setSize({ stateControlButtonSize.x * 0.5f, stateControlButtonSize.y });
    Option2x.setPosition({ speedOptionsX + stateControlButtonSize.x * 1 + 10, speedOptionsY }); // x = 240
    Option2x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option4x.setText("4x", 20);
    Option4x.setSize({ stateControlButtonSize.x * 0.5f, stateControlButtonSize.y });
    Option4x.setPosition({ speedOptionsX + stateControlButtonSize.x * 1.5f + 15, speedOptionsY }); // x = 300
    Option4x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Skip.setText("Skip", 20);
    Skip.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Skip.setPosition({ speedOptionsX + stateControlButtonSize.x * 2 + 30, speedOptionsY }); // x = 360
    Skip.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    // Middle row: Dijkstra, Prev, Pause, Next
    float middleRowY = bottomRowY - rowSpacing; // y = 810 (860 - 50)

    Dijkstra.setText("Dijkstra", 20);
    Dijkstra.setSize({ stateControlButtonSize.x, stateControlButtonSize.y }); // {300, 40}
    Dijkstra.setPosition({ operationBoardPosition.x, middleRowY });
    Dijkstra.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Prev.setText("Prev", 20);
    Prev.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Prev.setPosition({ operationBoardPosition.x + stateControlButtonSize.x, middleRowY });
    Prev.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Pause.setText("Pause", 20);
    Pause.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Pause.setPosition({ operationBoardPosition.x + stateControlButtonSize.x*2, middleRowY });
    Pause.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Next.setText("Next", 20);
    Next.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Next.setPosition({ operationBoardPosition.x + stateControlButtonSize.x*3, middleRowY });
    Next.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    // Top row: Random, Input, Load File, Edit
    float topRowY = middleRowY - rowSpacing; // y = 760 (810 - 50)

    Random.setText("Random", 20);
    Random.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Random.setPosition({ operationBoardPosition.x, topRowY });
    Random.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Input.setText("Input", 20);
    Input.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Input.setPosition({ operationBoardPosition.x + stateControlButtonSize.x, topRowY });
    Input.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    LoadFile.setText("Load File", 20);
    LoadFile.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    LoadFile.setPosition({ operationBoardPosition.x + stateControlButtonSize.x*2, topRowY });
    LoadFile.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Edit.setText("Edit", 20);
    Edit.setSize({ stateControlButtonSize.x, stateControlButtonSize.y });
    Edit.setPosition({ operationBoardPosition.x + stateControlButtonSize.x*3, topRowY });
    Edit.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    startVertexTextBox.setText("0");
}

ShPController::~ShPController() {}

void ShPController::update() {
    Random.update();
    Pause.update();
    Next.update();
    Prev.update();
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
		Skip.update();
        if (Skip.isClicked()) {
            currentSpeed = 10000000.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText("Skipping", 20);
        }
    }
}

void ShPController::render() {
    Random.drawRoundedRectangle(10);
    Pause.drawRoundedRectangle(10);
    Next.drawRoundedRectangle(10);
    Prev.drawRoundedRectangle(10);
    Input.drawRoundedRectangle(10);
    Dijkstra.drawRoundedRectangle(10);
    LoadFile.drawRoundedRectangle(10);
    Edit.drawRoundedRectangle(10);
    SpeedButton.drawRoundedRectangle(10);
    startVertexTextBox.render();

    Random.drawText(BLACK);
    Pause.drawText(BLACK);
    Next.drawText(BLACK);
    Prev.drawText(BLACK);
    Input.drawText(BLACK);
    Dijkstra.drawText(BLACK);
    LoadFile.drawText(BLACK);
    Edit.drawText(BLACK);
    SpeedButton.drawText(BLACK);
    Vector2 textPos = {700, 830};
    DrawText("Start Vertex", textPos.x, textPos.y, 20, BLACK);

    if (isSpeedDropdownOpen) {
        Option05x.drawRoundedRectangle(10);
        Option05x.drawText(BLACK);
        Option1x.drawRoundedRectangle(10);
        Option1x.drawText(BLACK);
        Option2x.drawRoundedRectangle(10);
        Option2x.drawText(BLACK);
        Option4x.drawRoundedRectangle(10);
        Option4x.drawText(BLACK);
		Skip.drawRoundedRectangle(10);
		Skip.drawText(BLACK);
    }
}

bool ShPController::isRandomClicked() const {
    return Random.isClicked();
}

bool ShPController::isPauseClicked() const {
    return Pause.isClicked();
}

bool ShPController::isNextClicked() const {
    return Next.isClicked();
}

bool ShPController::isPrevClicked() const {
    return Prev.isClicked();
}

void ShPController::setPauseText(const std::string& text) {
    Pause.setText(text.c_str(), 20);
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