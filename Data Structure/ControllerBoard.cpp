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
    Home.setTexture("../Resource/Icon/home-1-svgrepo-com.svg");
    //State Control Button in the middle bottom

    Begin.setSize(stateControlButtonSize);
    Begin.setPosition(stateControlPosition);
    Begin.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    Begin.setTexture("../Resource/Icon/rewind-forward-svgrepo-com.svg");


    Resume.setSize(stateControlButtonSize);
    Resume.setPosition({ stateControlPosition.x + stateControlButtonSize.x,stateControlPosition.y });
    Resume.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    Resume.setTexture("../Resource/Icon/pause-svgrepo-com.svg");

    Next.setSize(stateControlButtonSize);
    Next.setPosition({ stateControlPosition.x + 2*stateControlButtonSize.x,stateControlPosition.y });
    Next.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    Next.setTexture("../Resource/Icon/forward-svgrepo-com.svg");

    Prev.setSize(stateControlButtonSize);
    Prev.setPosition({ stateControlPosition.x + 3*stateControlButtonSize.x,stateControlPosition.y });
    Prev.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    Prev.setTexture("../Resource/Icon/reply-svgrepo-com.svg");

    End.setSize(stateControlButtonSize);
    End.setPosition({ stateControlPosition.x + 4 * stateControlButtonSize.x,stateControlPosition.y });
    End.SetColor(controllerIdleColor, controllerHoveringColor, controllerActiveColor);
    End.setTexture("../Resource/Icon/rewind-forward-svgrepo-com.svg");
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
    Home.renderRectangle();
    Home.drawTexture();
    Begin.renderRectangle();
    Begin.drawTexture();
    Resume.renderRectangle();
    Resume.drawTexture();
    Next.renderRectangle();
    Next.drawTexture();
    Prev.renderRectangle();
    Prev.drawTexture();
    End.drawTexture();
    End.renderRectangle();
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
