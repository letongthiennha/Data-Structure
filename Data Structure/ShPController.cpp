#include "ShPController.h"
#include "ShortestPath.h"
#include <string>

std::string ShPController::formatSpeed(float speed) {
    std::ostringstream oss;
    oss << "Speed: " << std::fixed << std::setprecision(1) << speed << "x";
    return oss.str();
}

ShPController::ShPController()
    : startVertexTextBox({ 0, 0 }, { stateControlButtonSize.x * 1.5f, stateControlButtonSize.y }, WHITE, BLACK, 2) {

    OperationBoard.x = operationBoardPosition.x;
    OperationBoard.y = operationBoardPosition.y;
    OperationBoard.width = operationBoardSize.x;
    OperationBoard.height = operationBoardSize.y;

    // Tính toán khoảng cách giữa các hàng
    float rowSpacing = stateControlButtonSize.y + 10;

    // Hàng dưới cùng (hàng cuối): Start Vertex và Speed
    float bottomRowY = stateControlPosition.y;

    startVertexTextBox.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 2, bottomRowY });

    SpeedButton.setText("Speed", 18);
    SpeedButton.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    SpeedButton.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 3.5f + 10, bottomRowY });
    SpeedButton.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    float speedOptionsX = SpeedButton.getPosition().x + stateControlButtonSize.x * 3.5f + 10;
    float speedOptionsY = bottomRowY;

    Option05x.setText("0.5x", 18);
    Option05x.setSize({ stateControlButtonSize.x * 1.5f, stateControlButtonSize.y });
    Option05x.setPosition({ speedOptionsX, speedOptionsY });
    Option05x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option1x.setText("1x", 18);
    Option1x.setSize({ stateControlButtonSize.x * 1.5f, stateControlButtonSize.y });
    Option1x.setPosition({ speedOptionsX + stateControlButtonSize.x * 1.5f + 5, speedOptionsY });
    Option1x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option2x.setText("2x", 18);
    Option2x.setSize({ stateControlButtonSize.x * 1.5f, stateControlButtonSize.y });
    Option2x.setPosition({ speedOptionsX + stateControlButtonSize.x * 3 + 10, speedOptionsY });
    Option2x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Option4x.setText("4x", 18);
    Option4x.setSize({ stateControlButtonSize.x * 1.5f, stateControlButtonSize.y });
    Option4x.setPosition({ speedOptionsX + stateControlButtonSize.x * 4.5f + 15, speedOptionsY });
    Option4x.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    // Hàng giữa: Dijkstra, Prev, Pause, Next
    float middleRowY = bottomRowY - rowSpacing;

    Dijkstra.setText("Dijkstra", 18);
    Dijkstra.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Dijkstra.setPosition({ stateControlPosition.x, middleRowY });
    Dijkstra.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Prev.setText("Prev", 18);
    Prev.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Prev.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 3 + 10, middleRowY });
    Prev.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Pause.setText("Pause", 18);
    Pause.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Pause.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 6 + 20, middleRowY });
    Pause.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Next.setText("Next", 18);
    Next.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Next.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 9 + 30, middleRowY });
    Next.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    // Hàng trên cùng: Random, Input, Load File, Edit
    float topRowY = middleRowY - rowSpacing;

    Random.setText("Random", 18);
    Random.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Random.setPosition({ stateControlPosition.x, topRowY });
    Random.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Input.setText("Input", 18);
    Input.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Input.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 3 + 10, topRowY });
    Input.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    LoadFile.setText("Load File", 18);
    LoadFile.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    LoadFile.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 6 + 20, topRowY });
    LoadFile.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Edit.setText("Edit", 18);
    Edit.setSize({ stateControlButtonSize.x * 3, stateControlButtonSize.y });
    Edit.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 9 + 30, topRowY });
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
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 18);
        }
        Option1x.update();
        if (Option1x.isClicked()) {
            currentSpeed = 1.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 18);
        }
        Option2x.update();
        if (Option2x.isClicked()) {
            currentSpeed = 2.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 18);
        }
        Option4x.update();
        if (Option4x.isClicked()) {
            currentSpeed = 4.0f;
            isSpeedDropdownOpen = false;
            SpeedButton.setText((formatSpeed(currentSpeed)).c_str(), 18);
        }
    }
}

void ShPController::render() {
    Random.drawRectangle();
    Pause.drawRectangle();
    Next.drawRectangle();
    Prev.drawRectangle();
    Input.drawRectangle();
    Dijkstra.drawRectangle();
    LoadFile.drawRectangle();
    Edit.drawRectangle();
    SpeedButton.drawRectangle();
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
    Vector2 textPos = { stateControlPosition.x, stateControlPosition.y + 25};
    DrawText("Start Vertex", textPos.x, textPos.y, 18, BLACK);

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
    Pause.setText(text.c_str(), 18);
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