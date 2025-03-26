#pragma once

#include "raylib.h"
const int speed = 200;
//===========TextBox================
const Color textBoxColor = DARKGRAY;
const Color textBoxColorInputing = LIGHTGRAY;
const int textBoxTextSize = 20;
const int textBoxTitleTextSize = 20;

//===========================ControllerBoard===================
//==========================Color===============
const Color controllerIdleColor{ 100,207,246,255 };
const Color controllerActiveColor=RED;
const Color controllerHoveringColor{ 85,156,236,255 };

//=========OperationBoard===============
const Vector2 operationBoardPosition;
const Vector2 operationBoardSize;

//========================StateControl Button
const Vector2 homeButtonPosition{ 50,50 };
const Vector2 stateControlButtonSize{ 60,60 };
const Vector2 stateControlPosition{ 620,840 };