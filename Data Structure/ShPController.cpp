#include "ShPController.h"
#include "ShortestPath.h"

ShPController::ShPController()
    : startVertexTextBox({ stateControlPosition.x + stateControlButtonSize.x * 6, stateControlPosition.y + stateControlButtonSize.y }, { stateControlButtonSize.x * 2, stateControlButtonSize.y }, WHITE, BLACK, 2) {


    OperationBoard.x = operationBoardPosition.x;
    OperationBoard.y = operationBoardPosition.y;
    OperationBoard.width = operationBoardSize.x;
    OperationBoard.height = operationBoardSize.y;

    Random.setText("Random", 18);
    Random.setSize({stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Random.setPosition(stateControlPosition);
    Random.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Input.setText("Input", 18);
    Input.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Input.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 2, stateControlPosition.y });
    Input.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    LoadFile.setText("Load File", 18);
    LoadFile.setSize({ stateControlButtonSize.x * 2, stateControlButtonSize.y });
    LoadFile.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 4, stateControlPosition.y });
    LoadFile.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Dijkstra.setText("Dijkstra", 18);
    Dijkstra.setSize({stateControlButtonSize.x * 2, stateControlButtonSize.y });
    Dijkstra.setPosition({ stateControlPosition.x + stateControlButtonSize.x * 6, stateControlPosition.y });
    Dijkstra.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    
    startVertexTextBox.setText("0");
}


ShPController::~ShPController() {}
void ShPController::update() {
    Random.update();
    Input.update();
    Dijkstra.update();
    LoadFile.update();
    startVertexTextBox.update();
}
void ShPController::render() {
	Random.drawRectangle();
	Input.drawRectangle();
	Dijkstra.drawRectangle();
    LoadFile.drawRectangle();
    startVertexTextBox.render();

    Random.drawText(BLACK);
    Input.drawText(BLACK);
    Dijkstra.drawText(BLACK);
    LoadFile.drawText(BLACK);
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
bool ShPController::isDijkstraClicked() const {
	return Dijkstra.isClicked();
}
int ShPController::getStartVertex() {
    std::string startVertexStr = startVertexTextBox.getText();
    return std::stoi(startVertexStr);
}
