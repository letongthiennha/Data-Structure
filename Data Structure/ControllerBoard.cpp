#include "ControllerBoard.h"
#include "Setting.h"

ControllerBoard::ControllerBoard() {

    //Operation Board
    OperationBoard.x = operationBoardPosition.x;
    OperationBoard.y = operationBoardPosition.y;
    OperationBoard.width = operationBoardSize.x;
    OperationBoard.height = operationBoardSize.y;

    //Home Button
    Home.setSize(stateControlButtonSize);
    Home.setPosition(homeButtonPosition);
    Home.SetColor(LIGHTGRAY, GRAY, DARKGRAY);

    //State Control Button in the middle bottom

    Begin.setSize(stateControlButtonSize);
    Begin.setPosition(stateControlPosition);
    Begin.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);

    Resume.setSize(stateControlButtonSize);
    Resume.setPosition({ stateControlPosition.x + stateControlButtonSize.x,stateControlPosition.y });
    Resume.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);


    Next.setSize(stateControlButtonSize);
    Next.setPosition({ stateControlPosition.x + 2*stateControlButtonSize.x,stateControlPosition.y });
    Next.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);


    Prev.setSize(stateControlButtonSize);
    Prev.setPosition({ stateControlPosition.x + 3*stateControlButtonSize.x,stateControlPosition.y });
    Prev.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);


    End.setSize(stateControlButtonSize);
    End.setPosition({ stateControlPosition.x + 4 * stateControlButtonSize.x,stateControlPosition.y });
    End.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
}

ControllerBoard::~ControllerBoard() {}

//Update State Control Button
void ControllerBoard::update() {
    // Update all buttons
    Home.update();
    Begin.update();
    Resume.update();
    Next.update();
    Prev.update();
    End.update();
}


//Render Control Button
void ControllerBoard::render() {
    // Draw buttons
    Home.drawRectangle();
    Begin.drawRectangle();
    Resume.drawRectangle();
    Next.drawRectangle();
    Prev.drawRectangle();
    End.drawRectangle();
}

bool ControllerBoard::isHomeClicked() const{
    return Home.isClicked();
}

bool ControllerBoard::isBeginClicked() const {
    return Begin.isClicked();
}

bool ControllerBoard::isResumeClicked() const {
    return Resume.isClicked();
}

bool ControllerBoard::isNextClicked() const {
    return Next.isClicked();
}

bool ControllerBoard::isPrevClicked() const {
    return Prev.isClicked();
}

bool ControllerBoard::isEndClicked() const {
    return End.isClicked();
}
