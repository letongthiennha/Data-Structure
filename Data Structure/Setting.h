#pragma once
#include <vector>
#include <string>
#include "raylib.h"
const int speed = 200;
const Font Arial= LoadFont("assets/Font/arial.ttf");
const Font StardewValley = LoadFont("assets/Font/StardewValley.ttf");
const Font Roboto = LoadFont("assets/Font/Roboto.ttf");
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
const Vector2 homeButtonSize{ 60,60 };

const Vector2 stateControlButtonSize{ 200,50 };
const Vector2 stateControlPosition{ 750,840 };



//===========================Node Color===================
const Color nodeIdleColor = WHITE;
const Color nodeHighLightColor = RED;
const Color nodeTextColor = BLACK;
const Color nodeTextHighlightColor = WHITE;


//========================LinkedList=======================
const float LinkedListDefaultSpeed = 1.0f;

const Color messageLogColor = BLUE;
const Color messageLogColorHighligth  = RED;

const int ListNodeSize = 50;
const Color ListNodeColor = WHITE;
const Color ListNodeTextColor = BLACK;
const Color ListNodeHighlightColor = BLUE;
const int pointerLength = 100;
const Vector2 LinkedListInitPosition{ 100,390 };
const Vector2 LinkedListCodeBlockPos{ 1200,400 };
//CodeBlock
const std::vector<std::vector<std::string>> SLLSourceCode = {
    {
        "Create:",
        " for (int i = 0; i < count; i++) {",
        "     int val = getRandomValue()",
        "     Node* newNode = new Node(val)",
        "     if (!pHead) {",
        "         pHead = newNode",
        "     } else {",
        "         Node* pCurr = pHead",
        "         while (pCurr->next) {",
        "             pCurr = pCurr->next",
        "         }",
        "         pCurr->next = newNode",
        "     }",
        " }"
    },
    {
        "Insert:",
        " newNode = new Node(val)",
        " if (!pHead) {",
        "     pHead = newNode",
        " } else {",
        "     pCurr = pHead",
        "     while (pCurr->next) {",
        "         pCurr = pCurr->next",
        "     }",
        "     pCurr->next = newNode",
        " }"
    },
    {
        "Remove:",
        " if (!pHead) return",
        " if (pHead->val == val){",
        "     Node* temp = pHead",
        "     pHead = pHead->next",
        "     delete temp}",
        " else {",
        "     while (pCurr->next)",
        "         if (pCurr->next->val == val)",
        "             {Node* temp = pCurr->next",
        "             pCurr->next = pCurr->next->next"
        "             delete temp}}",
    },
    {
        "Search:",
        " Node*pCurr = pHead",
        " while (pCurr)",
        "     if (pCurr->val == val) return",
    },
    {   "Update:",
        " Node*pCurr = pHead",
        " while (pCurr)",
        "     {if (pCurr->val == old)",
        "         pCurr->val = new}",
    }
};